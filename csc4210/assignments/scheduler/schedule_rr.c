/*
Names: Matt Burton, Emma Jerrier, William Phipps
Date: Apr 1 2024
Class: CCS4210
About: This program is designed to implement the round robin algorithm for executing a scheduled queue of tasks
Compile: make rr
Execute: ./rr rr-schedule.txt
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
    if (isFull(queue))
    {
        fprintf(stderr, "Cannot add tasks to a full queue\n");
        exit(2);
    }

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
   Postcondition: The first task in the queue is returned
*/
Task *pickNextTask(Queue *queue)
{
    if (isEmpty(queue))
    {
        fprintf(stderr, "Cannot pick the next task from an empty queue");
        exit(3);
    }

    return dequeue(queue);
}

/*
   Precondition: The schedule is called with a queue object containing a list of tasks
   Postcondition: The queue is output to the terminal before executing
                  Each task in the queue is executed in the order defined by pickkNextTask().
                  Tasks are removed from the queue and its memory is freed up
                  The average wait, response, and turn around times are output to the terminal
*/
void schedule(Queue *queue)
{
    if (isEmpty(queue))
    {
        fprintf(stderr, "Cannot process the schedule of an empty queue");
        exit(4);
    }

    // Output the total
    traverse(queue);

    // Initialize variables for tracking wait, response, and turn around times
    int numberOfTasks = queue->length;
    int totalTime = 0;
    int totalWaitTime = 0;
    int totalResponseTime = 0;
    int totalTurnAroundTime = 0;
    int processCounter = 0;

    // Loop through the queue until it is empty
    while (!isEmpty(queue))
    {
        // Pick the next task to run
        Task *task = pickNextTask(queue);

        // Increase total wait time
        totalWaitTime += totalTurnAroundTime - totalWaitTime;

        // Increase total response time the first time we handle each process
        if (processCounter < numberOfTasks)
        {
            processCounter++;
            totalResponseTime += totalTime;
        }

        // If the task requires less than a QUANTUM, run for the minimum required time
        if (task->burst < QUANTUM)
        {
            run(task, task->burst);
            totalTime += task->burst;
        }
        // Run the task for a QUANTUM time slice
        else
        {
            run(task, QUANTUM);
            totalTime += QUANTUM;
        }

        // Decrease burst by slice time
        task->burst -= QUANTUM;

        // Handle finished tasks
        if (task->burst <= 0)
        {
            // Calculate turnaround time
            totalTurnAroundTime += totalTime;

            // Free up memory assigned to finished tasks
            free(task);
        }
        // Handle unfinished tasks
        else
        {
            // Requeue the task
            enqueue(queue, task);
        }
    }

    // Output average wait, response, and turn around times
    printf("Average Wait Time: %.2f\n", (float)totalWaitTime / numberOfTasks);
    printf("Average Response Time: %.2f\n", (float)totalResponseTime / numberOfTasks);
    printf("Average Turn Around Time: %.2f\n", (float)totalTurnAroundTime / numberOfTasks);
}
