#include<sys/types.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
#include <ctype.h>

#define MAXLINE 1024
#define LISTENQ 1024
#define SERV_PORT 25565
//#define FD_SETSIZE 10
#define bool int
#define true 1
#define false 0

#define SA struct sockaddr

// Struct to hold information about each client
struct client_type {
   int cp[2]; // Pipe from child to parent
   int pc[2]; // Pipe from parent to child
   int id;    // Client ID/socket descriptor
   char user[20];
   char host[20];
   char realName[30];
};

const char *commands[] = {"USER ", "QUIT ", "JOIN ", "PART ", "TOPIC", "NAMES", "LIST ", "KICK ", "NICK "};

void child_proc(int sockfd, int readPipe, int writePipe);
void sig_child(int signc);
void distribute(struct client_type client[], int sender, char buff[], int n, int maxi);
int execCommand(struct client_type client[], char command[], char buff[], int n, int sender, int maxi, fd_set *allset);
void disconnect(struct client_type *client, fd_set *allset);

int main(int argc, char **argv)
{
    int i, maxi, maxfd, listenfd, connfd, pipefd, nready, commReceived, status;
    pid_t childpid[FD_SETSIZE];
    struct client_type client[FD_SETSIZE];
    size_t n;
    fd_set rset, allset;
    socklen_t cli_len;
    struct sockaddr_in cli_addr;
    struct sockaddr_in serv_addr;
    char buff[MAXLINE];

    // Create a server socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // Set up server address and port
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);  

    // Bind the server socket to the address and port
    bind(listenfd, (SA *) &serv_addr, sizeof(serv_addr));
    listen(listenfd, LISTENQ);

    // Initialize variables and file descriptor sets
    maxfd = listenfd;
    maxi = -1;
    for(i = 0; i < FD_SETSIZE; i++)
        client[i].id = childpid[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    signal(SIGCHLD, sig_child);  // Handle child process termination

    for(;;) {
        rset = allset;
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &rset)) {
            // Accept incoming connection
            cli_len = sizeof(cli_addr);
            connfd = accept(listenfd, (SA *) &cli_addr, &cli_len);

            i = 0;
            // Find an unused client slot
            while(client[i].id >= 0 && i < FD_SETSIZE)
                i++;
            if(i < FD_SETSIZE) {
                client[i].id = connfd; // Store client ID
            } else {
                printf("Too many clients!\n");
                exit(1);
            }

            // Create pipes for communication between child and parent
            pipe(client[i].cp);
            pipe(client[i].pc);

            if((childpid[i] = fork())==0){
                //Child Process
                close(listenfd);
                close(client[i].cp[0]);  // Close child's read end of cp
                close(client[i].pc[1]);  // Close child's write end of pc
                child_proc(connfd, client[i].pc[0], client[i].cp[1]); // Start child process
                exit(0);
            } else{
                //Parent Process
                close(connfd); // Close connection in parent
                close(client[i].cp[1]); // Close parent's write end of cp
                close(client[i].pc[0]); // Close parent's read end of pc

                strcpy(buff, "100");
                n = 3;
                write(client[i].pc[1], buff, n);

                FD_SET(client[i].cp[0], &allset);
                if(client[i].cp[0] > maxfd)
                maxfd = client[i].cp[0];
                if(i > maxi)
                maxi = i;
                if(--nready <= 0)
                continue;  // No more readable descriptors
            }
        }

        for(i = 0; i <= maxi; i++) {
            if((pipefd = client[i].cp[0]) < 0)
                continue;
            if(FD_ISSET(pipefd, &rset)) {
                if((n=read(pipefd,buff,MAXLINE)) == 0) {
                    // If no data, close pipe and clear the set
                    disconnect(&client[i], &allset);
                } else {
                    buff[n] = '\0';
                    printf("PARENT READ: %s\n",buff);
                    //Checking if input from client is a command
                    char command[MAXLINE];
                    if(n>=4){
                        for(int i = 0; i<5; i++)
                            command[i] = buff[i];
                        commReceived = 0;
                        for(int i = 0; i<9; i++){
                            if(strcmp(command,commands[i]) == 0 || strcmp(command, "QUIT") == 0){
                                if(strcmp(command, "QUIT") == 0)
                                    strcpy(command, "QUIT ");
                                commReceived = 1;
                            }
                        }
                    }
                    if(commReceived == 1){   //Command
                        printf("Command recieved\n");
                        status = execCommand(client, command, buff, n, i, maxi, &allset);
                        sprintf(buff, "%d", status);
                        n = 3;
                        if(status == 0)
                            n = 1;
                        buff[n] = '\0';
                        write(client[i].pc[1], buff, n);
                    } else {                    //Message
                        printf("Message recieved\n");
                        distribute(client, i, buff, n, maxi);
                    }
                    buff[0] = '\0';         //Resetting buffer after finished
                }
                if(--nready <= 0)
                    break;
            }
        }
    }
   
    return 0; 
}

// Function for child process
void child_proc(int sockfd, int readPipe, int writePipe)
{
    int nready;
    
    ssize_t n;
    char buff[MAXLINE];

    fd_set clientset, rset;
    FD_ZERO(&clientset);
    FD_SET(sockfd, &clientset);
    FD_SET(readPipe, &clientset);

    bool done = false;
    while(!done){
        rset = clientset;
        nready = select(readPipe+1, &rset, NULL, NULL, NULL);

        for(int i=0; i<=1; i++) {
            if(FD_ISSET(sockfd, &rset)) {
                if((n=read(sockfd,buff,MAXLINE))==0) {
                    close(sockfd);
                    close(readPipe);
                    FD_CLR(sockfd, &clientset);
                    FD_CLR(readPipe, &clientset);
                    done = true;
                } else {
                    buff[n] = '\0';
                    n--;
                    printf("CHILD READ FROM SOCKET: %s\n",buff);
                    write(writePipe, buff, n);
                    printf("CHILD WRITE TO PARENT: %s\n",buff);
                    strcpy(buff, " ");
                    buff[0] = '\0';
                }
                if(--nready <=0)
                    break;
            }else if(FD_ISSET(readPipe, &rset)) {
                if((n=read(readPipe,buff,MAXLINE))==0) {
                    close(readPipe);
                    close(sockfd);
                    FD_CLR(readPipe, &clientset);
                    FD_CLR(sockfd, &clientset);
                    done = true;
                } else {
                    printf("CHILD READ FROM PARENT: %s\n",buff);
                    write(sockfd, buff, n);
                    printf("CHILD WRITE TO SOCKET: %s\n",buff);
                    strcpy(buff, " ");
                    buff[0] = '\0';
                }
                if(--nready <=0)
                    break;
            }
        }
   }
}

// Function to handle child process termination
void sig_child(int signo)
{
    pid_t pid;
    int stat;

    while((pid = waitpid(-1, &stat, WNOHANG))>0)
        printf("Child %d terminated\n",pid);
}

void distribute(struct client_type client[], int sender, char buff[], int n, int maxi){
    //Finding length of sender's username
    int userLen = 2;
    while(client[sender].user[userLen-2] != '\0')
        userLen++;

    //Shifting buffer over to add username to message
    for(int i=1; i <= n; i++)
        buff[n+userLen-i] = buff[n-i];
    
    //Adding sender's username to the beginning of the mesage
    for(int i=0; i < userLen; i++)
        if(i < userLen-2)
            buff[i] = client[sender].user[i];
        else if(i == userLen - 2)
            buff[i] = ':';
        else
            buff[i] = ' ';
    n += userLen;

    //Sending the message to all the relevant clients
    int pipefd;
    for(int i=0; i<=maxi; i++) {
        if((pipefd = client[i].pc[1]) < 0)
            continue;
        else
            write(pipefd, buff, n);
    }
}

int execCommand(struct client_type client[], char command[], char buff[], int n, int sender, int maxi, fd_set *allset){
    if(strcmp(command,"USER ") == 0){
        //Retrieving data from parameters
        int i = 5;
        char params[4][30];
        for(int j = 0; j < 4; j++){
            int a = 0;
            char str[30];
            strcpy(str, "\0");
            while(buff[i] != ' ' && buff[i] != '\0' && i < n){
                str[a] = buff[i];
                i++;
                a++;
            }
            str[a] = '\0';
            strcpy(params[j], str);
        }
        strcpy(client[sender].user, params[0]);
        strcpy(client[sender].host, params[2]);
        strcpy(client[sender].realName, params[3]);
    }
    else if(strcmp(command, "QUIT ") == 0){
        char quitMsg[MAXLINE];
        int msgLen = 0;
        sprintf(quitMsg, "User %s has disconnected", client->user);
        while(quitMsg[msgLen] != '\0')
            msgLen++;
        if(n>5){    //Checking if quit message present
            strcat(quitMsg, ": ");
            msgLen += 2;
            for(int i = 5; i<n; i++)
                quitMsg[msgLen + (i-5)] = buff[i];
            msgLen += n-5;
        }

        distribute(client, sender, quitMsg, msgLen, maxi);

        disconnect(&client[sender], allset);
    }
    return 0;
}

void disconnect(struct client_type *client, fd_set *allset){
    close(client->cp[0]);
    close(client->pc[1]);
    client->user[0] = '\0';
    client->host[0] =  '\0';
    client->realName[0] = '\0';
    FD_CLR(client->cp[0], allset);
    client->id = client->cp[0] = client->pc[1] = -1;
}