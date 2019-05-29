
'''Req: A given system receives a bunch of tasks at beginning of day. 
task { 
  string id #assigned by this system as auto-incrementing string value
  int execTime
  list<task> children # all children becomes runnable as soon as this task completes
}
Note: When Task 1 is received, it may reference zero or more child tasks by id, but the child Task-55 details are only available when Task-55 description is seen later on. So it's best to store a list of child task ID's rather than pointers. The ID's can translate to Task pointers via a lookup table, either a map or array

Now, during the system initialization we need to calculate how long each task (and its subtree) will execute. I solved this problem with a top-down tree-walk with memoization

Now suppose this system expends to a farm of N identical cpu nodes. When a cpu completes a task, it can only [1] receive one specific runnable tasks, i.e. the one with smallest task ID. 

[1] an artificial constraint. I feel in a realistic context some other constraints may exist

I use two priorityQueues to hold two mutually exclusive subset of tasks. Any task not in these PQs are completed or blocked.

PQ: runnable: holds all runnable processes. This queue gets appended a group of tasks when group's parent task completes -- an (completion) event. This event time is predictable as soon as this parent task starts running on a cpu.

PQ: running: up to N tasks in the driver seats, sorted by expected end time. 

We will have an while loop. In each iteration, we pop the lowest item from the running queue, to simulate a task completion event, and add all its children to the runnable PQ. Then pop the leading runnable from this PQ and start it on the free node.

elegant

while-loop ends when the runnable queue becomes empty, and then running queue also becomes empty. The last event time is the total cost.

Note we don't enqueue tasks unrelated to the initial task (user input). We only care about the initial task and its subtree
'''