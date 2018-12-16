#ifndef MANAGER_H
#define MANAGER_H

#include "PCB.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <Windows.h>
#include "global_variables.h"
using namespace std;
class Manager{
private:
	queue<PCB * > * ready;			// queue of processing processes
	queue<PCB * > * processing;		// queue of ready processes
	queue<PCB * > * finished;		// queue of finished processes;
//	bool pro_push;					// if there is new processes to be pushed in
	int round_count;
	int pro_num;
	queue<PCB * > * process_list;	// queue for processes to be added, initialized in main();
	void project_adder();			// Function for adding process into ready list in timelet mode
public:
	Manager();
	~Manager();
	void manager_run_timelet();
	string ToString();
	void manager_run_fcfs();
};

Manager::Manager(){
	this -> ready = new queue<PCB *>();
	this -> processing = new queue<PCB *>();
	this -> finished = new queue<PCB *>();
	this -> process_list = new queue<PCB *>();
	this -> round_count = 0;
	/* Set the timelet value at the beginning of the procedure */
	cout << "Welcome!\nPlease input the system timelet:" << endl;
	cin.sync();
	int t = 0;
	cin >> t;
	cin.sync();
	set_timelet(t);

	/* This block requires users to input the preliminary process list */
	PCB* array[10];
	cout << "How many processes do you want to add to the list? \nNo more than 10" << endl;
	cin.sync();
	 int pro = 0;
	cin >> pro;
	this -> pro_num = pro;
	for (int i = 0; i < pro_num; i++){
		string nm;
		int pri, nt, rnd;
		cout << "Name of the process " << i << ":"<< endl;
		cin.sync();
		getline(cin, nm);
		cout << "Process " << nm << "'s priority (int):" << endl;
		cin.sync();
		cin >> pri;
		cout << "Process " << nm << "'s need time (int):" << endl;
		cin.sync();
		cin >> nt;
		cout << "Process " << nm << "'s cut-in round # (int):" << endl;
		cin.sync();
		cin >> rnd;
		PCB * tmp = new PCB(nm, pri, nt, rnd);
		array[i] = tmp;
	}
	/* No realization has been found to sort elements in queue
	 * A pop sort is realized here. 
	 * elements will be pushed into the queue one by one.
	 * In timelet round, processes will be pushed into the list
	 * according to their value of int round
	 * Complexity: n^2.
	 */
	for(int i = 0; i < this -> pro_num; i++){
		// array[i] = temp;
		PCB * temp_min = array[i];
//		int min_index = 0;
		for(int j = i + 1; j < pro_num; j++){
			if(array[j] -> round < array[i] -> round){
				temp_min = array[j];
				array[j] = array[i];
				array[i] = temp_min;
//				min_index = j;
			}
		}
		if(!this -> process_list -> empty()){
			this -> process_list -> back() -> append(temp_min);
		}
		this -> process_list -> push(temp_min);
	}

	cout << pro_num << "processes were added into system" << endl;
	


}

void Manager::project_adder(){
	if(!this -> process_list -> empty()){
		/* Loop here to ensure that processes with same round# can be added simultaneously*/
		for(int i = 0; i < (int)(this -> process_list -> size()); i++){
			if(this -> process_list -> front() -> round == this -> round_count){
				if(this -> ready -> empty() && this -> processing -> empty()){
					this -> processing -> push(this -> process_list -> front());
					this -> process_list -> pop();
					this -> processing -> front() -> run_the_process();
				}
				else{
					if(!this -> ready -> empty()){
						this -> ready -> back() -> append(this -> process_list -> front());
					}
					this -> ready -> push(this -> process_list -> front());
					this -> process_list -> pop();
				}
			}
			else{
				break;
			}
		}



	}
}

void Manager::manager_run_fcfs(){
	/* To avoid the break down of the procedure, there has to be a process
	 * for taking up spaces*/
	this -> ready -> push(new PCB("init_pro", 1, min(get_timelet(), process_list -> front()->round), 0));
	while(true){
		
		if(this -> process_list -> empty() && this -> processing -> empty() && this -> ready -> empty()){
			break;
		}
		Sleep(1000);
		/* Check if here is new process to be pushed in 
		 * In Every tick, there is possibility that a process
		 * is added into the queue for ready process		
		*/
		this -> project_adder();

		/* No matter what happen, each process has to be ticked();
		 * First, check whether new process
		 * All processes has to be ticked()!!!
		 */
		PCB * temp;
		/* Tick the ready queue; */
		for(int i = 0; i < this -> ready -> size(); i++){
			if(i == 0){
				temp = this -> ready -> front();
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();
		}
		/* check the tick of processing queue;*/
		if(this -> processing -> size() != 0){
			temp = this -> processing -> front();
			temp -> tick();
		}
		/* Check the tick() of finished queue;*/
		for(int i = 0; i < this -> finished -> size(); i++){
			if(i == 0){
				if(this -> finished -> size() == 0){
					break;
				}
				temp = this -> finished -> front();
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();
		}

		/* Determining the next position of relevant processes
		 * according to the current process after the tick.
		 * Altered status of each process is realized in its
		 * tick function.
		 * Note: status of processes in ready queue is altered here
		 * using PCB::run_the_process(), then altered process will be
		 * pushed into ```processing``` queue */
		
		if(this -> processing -> front() -> state == 'f'){
			this -> finished -> push(this -> processing -> front());
			this -> processing -> push(this -> ready -> front());
			this -> processing -> pop();
			this -> ready -> pop();
			this -> processing -> front() -> run_the_process();
		}
		/* Nothing is to be done if state == 'r' */
		this -> round_count ++;			// total count tick since boot

	}	
}

void Manager::manager_run_timelet(){
	/* To avoid the break down of the procedure, there has to be a process
	 * for taking up spaces*/
//	this -> ready -> push(new PCB("init_pro", 1, min(get_timelet(), process_list -> front()->round), 0));
	int cnt = 0;
	while(cnt < 1){
		if(this -> process_list -> empty() && this -> processing -> empty() && this -> ready -> empty()){
			break;
		}
		cout << this -> round_count << endl;
		if(this -> round_count == 9){
			cout << "";
			cin.sync();
		}
		Sleep(1000);
		/* Check if here is new process to be pushed in 
		 * In Every tick, there is possibility that a process
		 * is added into the queue for ready process		
		*/
		this -> project_adder();
		/* No matter what happen, each process has to be ticked();
		 * First, check whether new process
		 * All processes has to be ticked()!!!
		 */
		PCB * temp;
		/* Tick the ready queue; */
		for(int i = 0; i < ready -> size(); i++){
			if(i == 0){
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
				if(finished -> size() == 0){
					break;
				}
				temp = finished -> front();
			}
			else{
				temp = temp -> next_node;
			}
			temp -> tick();
		}


		/* Check the state of the process in the processing queue
		 * and determine the next location of each processes
		 *
		 * Right now, process to be yield is still in the processing queue
		 * when there is nothing to be processes, throw an error.*/
		
		if(!this -> processing -> empty()){
			temp = processing -> front();
			if (temp -> get_state() == 'p'){
				/* temp still continue doing */
				temp -> run_the_process();
			}
			else if (temp -> get_state() == 'f'){
				/* Append current process to finished list */
				if(!this -> finished -> empty()){
					this -> finished -> back() -> append(temp);
				}
				this -> finished -> push(temp);
				/* When there's process wating*/
				if(!this -> ready -> empty()){
					if(!this -> processing -> empty()){
						this -> processing -> back() -> append(this -> ready -> front());
					}
					this -> processing -> push(this -> ready -> front());
					this -> processing -> pop();
					this -> ready -> pop();
					this -> processing -> front() -> run_the_process();
				}
				/* When ready queue is empty, break the cycle, stop ticking*/
				else{
					break;
				}
			}
			else if (temp -> get_state() == 'r'){
				if (!this -> ready -> empty()){
					this -> processing -> back() -> append(this -> ready -> front());
					this -> processing -> push(this -> ready -> front());
					this -> ready -> push(this -> processing -> front());
					this -> ready -> pop();
					this -> processing -> pop();
					this -> processing -> front() -> run_the_process();
				}
				else{
					temp -> run_the_process();
				}
			}
		}
		else{
			cerr << "No process in under processing" << endl;
		}
		this -> round_count ++;			// total count tick since boot
		// cout << this ->ToString() << endl;
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

Manager::~Manager() {

}


#endif




