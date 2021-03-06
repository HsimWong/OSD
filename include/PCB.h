#ifndef PCB_H
#define PCB_H 
#include <string>
#include "global_variables.h"
#include <iostream>
using namespace std;


/*
 * This document describe the node of a process
 * the action taken here as well as criteria for determining
 * each situation is before the tick
 */

class PCB{
public:
	int priority;			// priotity
	int cpu_time;			// ticks since process established
	int need_time;			// ticks still needed
	int count;				// exact time used by the process
	int timelet_count;		// ticks run in a timelet_count
	// bool CurRunning;		// whether PCB is processed by CPU right now

	int round;				// Which round should the process be pushed in ready
	string name;			// process name
	char state;				// process state enum{'r = ready'. 'p = processing', 'f = finish'}
	PCB * next_node;		// ptr of next process
	// PCB();
	PCB(string name, int priority, int need_time, int round);
	~PCB();
	bool operator < (PCB p)const{
		return (this -> round) < (p.round);
	}
	bool tick();
	bool tick_fcfs();
	bool run_the_process();
	bool run_in_timelet();
	bool yield_resouce();
	char get_state();
	bool append(PCB * next_node);
	// short cmp_round(const PCB * a, const PCB * b);
	string ToString();
};

PCB::PCB(string name, int priority, int need_time, int round){
	this -> name = name;
	this -> priority = priority;
	this -> need_time = need_time;
	this -> next_node = NULL;
	this -> round = round;
	this -> cpu_time = 0;
	this -> timelet_count = 0;
	this -> count = 0;
	this -> state = 'r';
}

PCB::~PCB(){
	delete & (this -> name);
	delete &(this -> priority);
	delete &(this -> need_time);
	delete &(this -> next_node);
	delete &(this -> cpu_time);
	delete &(this -> timelet_count);
	delete &(this -> count);
	delete &(this -> state);
}

bool PCB::run_the_process(){
	if(this -> state == 'f'){
		return false;
	}
	else{
		this -> state = 'p';
		// cout << this -> name << " is processing." << endl;
		return true;
	}
}

bool PCB::yield_resouce(){
	if(this -> state == 'p'){
		// timelet up
		if(this -> need_time != 0) {
			if (this->timelet_count == 0) {
				this->state = 'r';
				return true;
			}
			else{
				cerr << "Called yield_resource() when still have need_time";
				return false;
			}
		}
		else{
			this -> state = 'f';
			return true;
		}
	}
	else{
		cerr << "The process is not running when required to yield timelet" << endl;
		return false;
	}
}

bool PCB::tick(){
	if(this -> state != 'f'){
		/* cpu_time increase in 'p' and in 'r'
		 * increase cpu_time does not alter any locks */
		this -> cpu_time ++;
		if(this -> state == 'p'){
			this -> count++;
			if(this -> timelet_count < get_timelet()){
				this -> timelet_count ++;
				this -> need_time --;
				/* when timelet is used up*/
				if(this -> timelet_count == get_timelet()){
					this -> timelet_count = 0;
					yield_resouce();
					return true;
				}
				if(this -> need_time == 0){
					yield_resouce();
					return true;
				}
			}
			else{
				cerr << "timelet error occur" << endl;
				return false;

			}
		}
		return true;
	}
	else{
		return true;
	}
}

bool PCB::tick_fcfs(){
	if(this -> state != 'f'){
		this -> cpu_time ++;
		if(this -> state == 'p'){
			this -> count ++;
			this -> timelet_count = (this -> timelet_count + 1) % get_timelet();
			this -> need_time --;
			if(this -> need_time == 0){
				this -> state = 'f';
			}
		}
		/* next state of 'r' process is realised outside
		 * after tick() */
	}
}



char PCB::get_state(){

	return this -> state;
}

bool PCB :: append(PCB * next_node){
	this -> next_node = next_node;
	return true;
}

string PCB::ToString(){
	string str = "";
	str = this -> name + "\t" + to_string(this -> state)
	+ "\t" + to_string(this -> priority) + "\t" + to_string(this -> round)
	+ "\t" + to_string(this -> count) + "\t" + to_string(this -> need_time)
	+ "\n";
	return str;
}

#endif
