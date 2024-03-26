/*
Names: Matt Burton, Emma Jerrier, William Phipps
Date: Mar 26 2024
Class: CCS4210
About: This program is designed to implement the first come first serve algorithm when executing a scheduled queue of task
Compile: make fcfs
Execute: ./fcfs schedule.txt
*/
#include "queue.h"
#include "task.h"
#include "cpu.h"
#include "schedulers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
   Precondition:  A queue is passed in that is not already full
                  Details about the new task are are also passed in
   Postcondition: Memory is allocated for the new task
                  The new task is entered into the queue
*/
void add(Queue *queue, char *name, int priority, int burst)
{
   // Create the new task id
   int tid = queue->length + 1;

   // Allocate memory for a new task
   Task *task = (Task *)malloc(sizeof(Task));
   if (task == NULL)
   {
      // Handle memory allocation failure
      fprintf(stderr, "Memory allocation failed\n");
      exit(1);
   }

   // Assign task values
   task->name = strdup(name);
   task->tid = tid;
   task->priority = priority;
   task->burst = burst;

   // Enter the task into the queue
   enqueue(queue, task);
}

/*
   Precondition: This funciton is called with a queue passed in containing zero or more tasks
   Postcondition: The first task in the queue is returned and removed from the queue
*/
Task *pickNextTask(Queue *queue)
{
   // Returns the first task in the queue and removes it from the queue
   return dequeue(queue);
}

/*
   Precondition: The schedule is called with a queue object containing a list of tasks
   Postcondition: Each task in the queue is executed in the order defined by pickNextTask().
                  After a task is executed it is removed from the queue and its memory is freed up
                  The queue is emptied
*/
void schedule(Queue *queue)
{
   traverse(queue);

   // Loop through the queue until it is empty
   while (!isEmpty(queue))
   {
      // Pick the next task to run
      Task *task = pickNextTask(queue);

      // Run the next task for a QUANTUM time slice
      run(task, task->burst);

      // Free up the memory assigned by malloc
      free(task);
   }
}
