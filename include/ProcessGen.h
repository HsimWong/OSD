#ifndef PROCESSGEN_H
#define PROCESSGEN_H 
#include "PCB.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#define MIN 1				
#define MAX 50				// maximum and minimum value of priorities and time 2b consumed
using namespace std;

class ProcessGen
{
private:
	bool pro_gened;
	int ind_count;
	PCB * process;
public:
	ProcessGen();
	~ProcessGen();
	// bool new_pro();
	PCB * take_new_pro(int round);
};


ProcessGen::ProcessGen(){
	this -> pro_gened = false;
	this -> ind_count = 0;
}

PCB * ProcessGen::take_new_pro(int round){	
	string name = "Process_" + to_string(this -> ind_count);
	srand((unsigned)time(0));
	int priority = MIN + (int)MAX * rand() / (RAND_MAX + 1);
	int need_time = MIN + (int)MAX * rand() / (RAND_MAX + 1);
	// int round controlling is defined in file Manager.h
	this -> process = new PCB(name, priority, need_time, round);
	
	cout << "Process named " << name << " is added into Ready queue" << endl;
	this -> ind_count ++;

	return this -> process;

}





#endif
