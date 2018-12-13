#include "PCB.h"
#include <iostream>
#include "Queue.h"
#include "gloval_variables.h"
using namespace std;

class Manager{
private:
	Queue * processing;		// queue of processing processes
	Queue * ready;			// queue of ready processes
	Queue * finished;		// queue of finished processes;
	bool pro_push;			// if there is new processes to be pushed in

public:
	Manager();
	~Manager();
	void new_process(PCB * p);
	void manager_run();

};

void Manager::Manager(){
	this -> ready = new Queue();
	this -> processing = new Queue();
	this -> finished = new Queue();
}

void Manager::new_process(PCB * p){
	this -> ready -> push(p);
	return;
}


void Manager::manager_run(){
	while(true){
		// No matter what happen, each process has to be ticked();
		// First, check whether new process
		// All processes has to be ticked()!!!
		PCB * temp;
		// Check the ready queue;
		for(int i = 0; i < ready -> get_capacity(); i++){
			if(i == 0){
				temp = ready -> head;
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();
		}
		// check the processing queue;
		temp = processing -> head;
		temp -> tick();
		// Check the finished queue;
		for(int i = 0; i < finished -> get_capacity(); i++){
			if(i == 0){
                                temp = finished -> head;
                        }
                        else{
                                temp = temp -> next_node;
                        }
			temp -> tick();
		}


		// Check the state of the process in the processing queue
		// and determine the next location of each processes
		

		temp = processing -> head;
		if (temp -> get_state() == 'p'){
			continue;
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
		}
	//	if(temp -> get_state() != 'f' || this -> ready -> get_capacity() == 0){
	//		temp -> run_the_process();
	//		
	//	}
	//	else if(temp -> get_state == 'f'){
	//		temp -> 	
	//	}

	}
}







