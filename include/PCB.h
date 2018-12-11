#ifndef PCB_H
#define PCB_H 
#include <string>
#include "global_variables.h"
#include <iostream>
using namespace std;

class PCB{
private:
	string name;			// process name
	int priority;			// priotity
	// int round;
	int cpu_time;			// ticks since process established
	int need_time;			// ticks still needed
	int count;				// exact time used by the process
	int timelet_count;		// ticks run in a timelet_count
	// bool CurRunning;		// whether PCB is processed by CPU right now
	char state;				// process state enum{'r = ready'. 'p = processing', 'f = finish'}
	
public:
	PCB * next_node;
	PCB(string name, int priority, int need_time, PCB * next_node = NULL);
	bool operator < (PCB p){
		return (this -> round) < (p.round);
	}
	bool tick();
	bool run_the_process();
	bool run_in_timelet();
	bool yield_resouce();
	char get_state();
	bool append(PCB * next_node);
};
	


PCB::PCB(string name, int priority, int need_time, PCB * next_node = NULL){
	this -> name = name;
	this -> priority = priority;
	this -> need_time = need_time;
	this -> next_node = next_node;
	this -> cpu_time = 0;
	this -> timelet_count = 0;
	this -> count = 0;
	this -> state = 'r';
}

PCB::~PCB(){
	delete [] this -> name;
	delete [] this -> priority;
	delete [] this -> need_time;
	delete [] this -> next_node;
	delete [] this -> cpu_time;
	delete [] this -> timelet_count;
	delete [] this -> count;
	delete [] this -> state;
}

bool PCB::run_the_process(){
	if(this -> state == 'p' || this -> state == 'f'){
		return false;
	}
	else{
		this -> state = 'p';
		return true;
	}
}

bool PCB::yield_resouce(){
	this -> CurRunning = false;
	return true;
}

bool PCB::run_in_timelet(){
	if (this -> CurRunning == false)	{
		return false;
	}
	else{
		return true;
	}
}

bool PCB::tick(){
	if(this -> state != 'f'){
		// cpu_time increase in 'p' and in 'r'
		this -> cpu_time ++;
		if(this -> state == 'p'){
			if(this -> timelet_count < timelet){
				this -> timelet_count ++;
				this -> need_time --;
				// when timelet is used up
				if(this -> timelet_count == timelet){
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

char PCB::get_state(){
	return this -> state;
}


bool PCB :: append(PCB * next_node){
	this -> next_node = next_node;
	return true;
}

#endif