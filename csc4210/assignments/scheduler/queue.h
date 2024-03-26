/**
 * queue data structure containing the tasks in the system
 */

#include "task.h"

typedef struct node {
    Task *task;
    struct node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    int length;
} Queue;

//bool is not defined in C so how about
//an unsigned char = we only need 0 and 1
typedef unsigned char bool;
#define true 1
#define false 0

// insert and delete operations.
void create(Queue *);
int length(Queue *queue);
bool isEmpty(Queue *queue);
bool isFull(Queue *queue);
void enqueue(Queue *, Task *task);
Task* dequeue(Queue *);
void delete(Queue *, Task *task);
void traverse(Queue *);
