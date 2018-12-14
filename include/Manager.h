#include "PCB.h"
#include <iostream>
#include <fstream>
#include "Queue.h"
#include <ctime>
#include "ProcessGen.h"
// #include "gloval_variables.h"
using namespace std;


ProcessGen * pg = new ProcessGen();


class Manager{
private:
	Queue * processing;		// queue of processing processes
	Queue * ready;			// queue of ready processes
	Queue * finished;		// queue of finished processes;
	bool pro_push;			// if there is new processes to be pushed in
	int round_count;
public:
	Manager();
	~Manager();
	void new_process(PCB * p);
	void manager_run();
	void process_listener();

};

Manager::Manager(){
	this -> ready = new Queue();
	this -> processing = new Queue();
	this -> finished = new Queue();
	this -> round_count = 0;
	PCB * insert = new PCB("ProcessListener", 1, INFINITY, round_count);		// a process for inserting new process
	this -> ready -> push(insert);
	return;
}

void Manager::new_process(PCB * p){
	this -> ready -> push(p);
	return;
}

void Manager::process_listener(){
	srand((unsigned)time(0));
	if()
} 

void Manager::manager_run(){
	while(true){
		/* Check if here is new process to be pushed in */
		pg -> 




		// No matter what happen, each process has to be ticked();
		// First, check whether new process
		// All processes has to be ticked()!!!
		PCB * temp;
		// Check the ready queue;
		for(int i = 0; i < ready -> get_capacity(); i++){
			if(i == 0){
				temp = ready -> top();
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();
		}
		// check the tick of processing queue;
		temp = processing -> top();
		temp -> tick();
		// Check the tick() of finished queue;
		for(int i = 0; i < finished -> get_capacity(); i++){
			if(i == 0){
				temp = finished -> top();
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();
		}


		/* 
		 * Check the state of the process in the processing queue
		 * and determine the next location of each processes
		 *
		 * Right now, process to be yield is still in the processing queue
		 * when there is nothing to be processes, throw an error.
		 */
		// if(this -> ready -> get_capacity + this -> processing ->)
		if(this -> processing -> isEmpty() == false){
			temp = processing -> top();
			if (temp -> get_state() == 'p'){
				if (temp -> name == "ProcessListener"){
					process_listener();
				}
			}
			else if (temp -> get_state() == 'f'){
				this -> finished -> push(temp);
				this -> processing -> push(this -> ready -> top());
				this -> processing -> pop();
				this -> ready -> pop();
			}
			else if (temp -> get_state() == 'r'){
				this -> processing -> push(this -> ready -> top());
				this -> ready -> pop();
				this -> ready -> push(this -> processing -> top());
				this -> processing -> pop();
				this -> processing -> top() -> run_the_process();
			}
		}
		else{
			cerr << "No process in under processing" << endl;
		}

		this -> round_count ++;			// total count tick since boot
	}
}







