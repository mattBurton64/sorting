/**
 * Various queue operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "task.h"

//create a queue with a dummy header
//queue is empty if both front and rear
//point to the dummy header
//front always points to the dummy
void create(Queue *queue)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->next=NULL;
    queue->front=queue->rear=temp;
    queue->length=0;
}

// length of queue
int length(Queue *queue)
{
    return queue->length;
}

// is the queue empty?
bool isEmpty(Queue *queue)
{
    return (queue->length == 0); 
}

// is the queue full?
bool isFull(Queue *queue)
{
    // ran out of memory?
    Node *testNode = malloc(sizeof(Node));
    bool rv = (testNode == NULL);
    if(!rv)
        free(testNode);
    return rv;
}

// add a new task to the list of tasks
void enqueue(Queue *queue, Task *newTask) 
{
    // add the new task to the list 
    Node *newNode = malloc(sizeof(Node));
    newNode->task = newTask;
    newNode->next = NULL;
    queue->rear->next = newNode;
    queue->rear = newNode;
    queue->length++;
}

// dequeue the front task and return it
Task * dequeue(Queue *queue) 
{
    if(queue->front!=queue->rear) {
       Node *prev = queue->front;
       Node *temp = prev->next;
       Task *task;

       //remove a task
       prev->next = temp->next;

       //is queue empty?
       if(temp==queue->rear)
           queue->rear=queue->front;

       queue->length--;
       //prepare to return task
       task = temp->task;
       free(temp);
       return task;
    } else {
        return NULL;
    }
}


// delete a specific task from the queue
void delete(Queue *queue, Task *task) 
{
   if(queue->front!=queue->rear) {
      Node *prev=queue->front;
      Node *temp=prev->next;
      while(temp!=NULL && strcmp(task->name,temp->task->name) != 0) {
         prev = temp;
         temp = temp->next;
      }
      //did we find the node?
      if(temp!=NULL) {
         queue->length--;
         prev->next = temp->next;
         //are we at the end?
         if(temp==queue->rear)
            queue->rear=prev;
         free(temp);
      }
   }
}

// traverse the list
void traverse(Queue *queue) {
    Node *temp;
    temp = queue->front->next;

    while (temp != NULL) {
        printf("[%s] [%d] ",temp->task->name, temp->task->priority);
        printf("[%d]\n", temp->task->burst);
        temp = temp->next;
    }
}
