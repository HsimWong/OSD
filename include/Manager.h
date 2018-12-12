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
	

};

void Manager::Manager(){
	this -> ready = new Queue();
	this -> processing = new Queue();
	this -> finished = new Queue();
}

void Manager::new_process(PCB * p){
	this -> ready -> push(p);
}

void process(){
	if(ready -> get_capacity() == 0){
		cerr << "ready queue has 0 processes";
	}
	else{
		cout << processing -> head -> name << "is processing" << endl;
	}
}

Manager::manager_run(){
	while(true){
		PCB * temp;
		for(int i = 0; i < ready -> get_capacity(); i++){
			if(i == 0){
				temp = ready -> head;
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();
		}

		for(int i = 0; i < processing -> get_capacity(); i++){
			if(i == 0){
				temp = ready -> head;
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();

		}
	}
}

