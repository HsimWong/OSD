#include "PCB.h"
#include <iostream>
#include <fstream>
#include "Queue.h"
#include <queue>
#include <ctime>
#include "ProcessGen.h"
#include <windows.h>
// #include "gloval_variables.h"

using namespace std;


ProcessGen * pg = new ProcessGen();


class Manager{
private:
	queue<PCB * > * processing;		// queue of processing processes
	queue<PCB * > * ready;			// queue of ready processes
	queue<PCB * > * finished;		// queue of finished processes;
//	bool pro_push;			// if there is new processes to be pushed in
	int round_count;
public:
	Manager();
	~Manager();
	void new_process(PCB * p);
	void manager_run();
	void process_listener();
	string ToString();

};

Manager::Manager(){
	this -> ready = new queue<PCB *>();
	this -> processing = new queue<PCB *>();
	this -> finished = new queue<PCB *>();
	this -> round_count = 0;

	PCB * insert = new PCB("ProcessListener", 1, INFINITY, round_count);		// a process for inserting new process
	insert -> run_the_process();
	this -> processing -> push(insert);

	for (int i = 0; i < 5; ++i) {
		insert = new PCB("PreProcess_" + to_string(i), 1, 3, 0);
		this -> ready -> push(insert);
	}

	return;
}

void Manager::new_process(PCB * p){
	this -> ready -> push(p);
	return;
}


// Insert new process to the ready queue at random time
void Manager::process_listener(){
	srand((unsigned)time(0));
	if((double)rand() / RAND_MAX < 1){
		this -> ready -> push(pg -> take_new_pro(this -> round_count));
		// cout << "Process named " <<name << " is added into Ready queue" << endl;
	}
	return;
} 

void Manager::manager_run(){

	int cnt = 0;
	while(cnt < 1){

		Sleep(1000);
//		cout << "ready length:" << this -> ready -> size() << endl;
		/* Check if here is new process to be pushed in 
		 * In Every tick, there is possibility that a process
		 * is added into the queue for ready process		
		*/
//		process_listener();
		// No matter what happen, each process has to be ticked();
		// First, check whether new process
		// All processes has to be ticked()!!!
		PCB * temp;
		// Check the ready queue;
//		cout << "ready length:" << this -> ready -> size() << endl;
		for(int i = 0; i < ready -> size(); i++){
			if(i == 0){
				// if(ready -> size() == 0){
				// 	break;
				// }
				temp = ready -> front();
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();
		}
		// check the tick of processing queue;
		if(processing -> size() != 0){

			temp = processing -> front();
			temp -> tick();
		}
		// Check the tick() of finished queue;
		for(int i = 0; i < finished -> size(); i++){
			if(i == 0){
				// if(finished -> size() == 0){
				// 	break;
				// }
				temp = finished -> front();
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

//		if(!this -> ready -> empty() &&){
//
//		}
		if(!this -> processing -> empty()){
			temp = processing -> front();
			if (temp -> get_state() == 'p'){
				// if (temp -> name == "ProcessListener"){
				// 	process_listener();
				// }
//				cout << temp -> ToString() << endl;
			}
			else if (temp -> get_state() == 'f'){
				this -> finished -> push(temp);
				this -> processing -> push(this -> ready -> front());
				this -> processing -> pop();
				this -> ready -> pop();
			}
			else if (temp -> get_state() == 'r'){
				this -> processing -> push(this -> ready -> front());
				this -> ready -> push(this -> processing -> front());
				this -> ready -> pop();

				this -> processing -> pop();
				this -> processing -> front() -> run_the_process();
			}
		}
		else{
			cerr << "No process in under processing" << endl;
		}

		this -> round_count ++;			// total count tick since boot
		cout << this ->ToString() << endl;
	}
}

string Manager::ToString(){
	string str = "";
	PCB * ptr = this -> processing -> front();
	str = "*************************************\nProcessing Queue info\n";
	for(int i = 0; i < this -> processing -> size(); i++){
		str += ptr -> ToString();
		ptr = ptr -> next_node;
	}
	str += "***********************************\nReady Queue info\n";
	ptr = this -> ready -> front();
	for(int i = 0; i < this -> processing -> size(); i++){
		str += ptr -> ToString();
		ptr = ptr -> next_node;
	}
	str += "***********************************\nFinished Queue info\n";
	ptr = this -> finished -> front();
	for (int i = 0; i < this -> finished -> size(); i++){
		str += ptr -> ToString();
		ptr = ptr -> next_node;
	}
	return str;
}







