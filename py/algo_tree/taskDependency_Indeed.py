
'''Req: A given system receives a bunch of tasks at beginning of day. 
task { 
  string id #assigned by this system as auto-incrementing string value
  int execTime
  list<task> children # all children becomes runnable as soon as this task completes
}
When Task 1 is received, it may reference zero or more child tasks by id, but the child task 55 details are only available when Task 55 description is seen later on.

So during the system initialization we need to calculate how long each task (and its subtree) will execute.

Now suppose this system is a farm consisting of N identical compute nodes. When a node completes a task, it can only receive one of the runnable tasks, i.e. the smallest task id.

PQ: runnable -- holds (probably more than) all runnable processes.
PQ: running -- up to N tasks in the driver's seat, sorted by expected end time. In each iteration, we pop the lowest item and add all its children to the runnable PQ. Then pop the leading runnable from this PQ and start it on the free node.
'''