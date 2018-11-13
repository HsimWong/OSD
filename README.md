# Operating System Software Design - Simulation on Process Dispatching and Simulation on DOS
This project is for the final project of the Operating System Software Disign, which is composed of two tasks: Process dispatching simulation and DOS. In the next few weeks, this project will be finished and documented respectively. All commits and pushes will record the activitiness during this period.
## Process Dispatching Simulation
A dispatching algorithm for managing process queue is required. Any process proposes their requests in the following format:


'''c
<code>
typedef struct node{
	char name[10];		// Notation string of the process
	int prio;			// Priority of the process
	int round;			
	int cputime;
	int needtime;
	int count;
	char state;
	struct node * next;
}PCB;
</code>
'''