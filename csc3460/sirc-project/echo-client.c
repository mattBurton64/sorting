#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include <curses.h> // importing ncurses to separate text input from conversation log
#include <pthread.h>

#define MAXLINE 1024
#define SERV_PORT 25565

#define SA struct sockaddr

bool debug = false; // true to turn on debugging features

void str_cli(WINDOW *inputWin, WINDOW *outputWin, int sockfd);
void CatchInterrupt (int signum);


struct ThreadArgs {
    int sockfd;
    WINDOW *outputWin;
};

void *receive_from_server(void *args) {
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
    int sockfd = threadArgs->sockfd;
    WINDOW *outputWin = threadArgs->outputWin;
    char recvline[MAXLINE];
    ssize_t recv_bytes;

    while ((recv_bytes = read(sockfd, recvline, MAXLINE - 1)) > 0) {
        recvline[recv_bytes] = '\0';
        wprintw(outputWin, "Server: %s\n", recvline);
        wrefresh(outputWin);
    }

    if (recv_bytes == 0) {
        wprintw(outputWin, "Server closed the connection.\n");
        wrefresh(outputWin);
    } else {
        perror("Error in receiving data from server");
        // Handle or print the error in the ncurses window if needed
    }

    return NULL;
}

int main(int argc, char **argv)
{
   int sockfd;
   struct sockaddr_in servaddr;


   signal(SIGINT, CatchInterrupt);

   if(argc != 2) {
      printf("Usage: a.out <IPaddress>\n");
      exit(1);
   }

   if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      printf("socket error\n");
      exit(2);
   }

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(SERV_PORT); 
   if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
      printf("inet_pton error for %s\n", argv[1]);

   if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
      printf("connect error\n");
   
   // Initialize NCurses
   initscr();
   cbreak();
   noecho();

   int inputWinHeight = 3; // Height of the input window (including line)
   int outputWinHeight = LINES - inputWinHeight - 1; // Rest of the space for output window

   WINDOW *outputWin = newwin(outputWinHeight, COLS, 0, 0);
   scrollok(outputWin, TRUE);

   WINDOW *inputWin = newwin(inputWinHeight, COLS, outputWinHeight, 0);
   mvwhline(inputWin, 0, 0, ACS_HLINE, COLS); // Horizontal line at the top

   wrefresh(outputWin);
   wrefresh(inputWin);

   struct ThreadArgs threadArgs;
   threadArgs.sockfd = sockfd;
   threadArgs.outputWin = outputWin;

   pthread_t recv_thread;
   pthread_create(&recv_thread, NULL, receive_from_server, &threadArgs);

   str_cli(inputWin, outputWin, sockfd); // Pass both windows to your function

   pthread_cancel(recv_thread);  // Terminate the receiving thread


   endwin(); // End NCurses
   close(sockfd);
   exit(0);
}

void str_cli(WINDOW *inputWin, WINDOW *outputWin, int sockfd) {
   char sendline[MAXLINE];
   char recvline[MAXLINE];

   bool done = false;
   while (!done) {
      if (debug) wprintw(outputWin, "Looping...\n");
      wrefresh(outputWin);
      // Get user input
      wmove(inputWin, 1, 1); // Move cursor to input window
      echo();
      wgetnstr(inputWin, sendline, MAXLINE - 1);
      noecho();

      // Clear input area
      werase(inputWin);
      mvwhline(inputWin, 0, 0, ACS_HLINE, COLS); // Redraw the horizontal line

      // Display user input in output window
      if (debug)
      {
         wprintw(outputWin, "Client: %s\n", sendline);
         wrefresh(outputWin);
      }

      // Send the user input to the server and get the response
      write(sockfd, sendline, strlen(sendline) + 1);
      ssize_t recv_bytes = read(sockfd, recvline, MAXLINE - 1);

      if (recv_bytes > 0) {
         recvline[recv_bytes] = '\0'; // Ensure proper string termination
         // Display server response in output window below previous messages
         wprintw(outputWin, "Server: %s\n", recvline);
         wrefresh(outputWin);
      } else if (recv_bytes == 0) {
         // Handle server closed connection
         done = true;
      } else {
         // Handle error in receiving data from the server
         perror("Error in receiving data from server");
         // Handle or exit as needed
      }

      if (strcmp(sendline, "exit") == 0 /*&& strcmp(recvline, "exit") == 0*/)
         done = true;

      // Clear the receive buffer for the next iteration
      memset(recvline, 0, sizeof(recvline));
   }
}


void CatchInterrupt (int signum) 
{
   pid_t my_pid;

   printf("\nReceived an interrupt! About to exit ..%d\n",signum);
   fflush(stdout);
   my_pid = getpid();
   kill(my_pid, SIGKILL);
}