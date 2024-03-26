/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice) {
    printf("Running task = [%s] [%d] ",task->name, task->priority);
    printf("[%d] for %d units.\n", task->burst, slice);
}
