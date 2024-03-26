#define MIN_PRIORITY 1
#define MAX_PRIORITY 10


// add a task to the list 
void add(Queue *, char *name, int priority, int burst);

// invoke the scheduler
void schedule(Queue *);

//select the next Task from the queue
Task* pickNextTask(Queue *queue);
