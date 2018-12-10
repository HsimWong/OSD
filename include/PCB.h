#ifndef PCB_H
#define PCB_H 
#include <string>
#include <iostream>
using namespace std;

class PCB{
private:
	string name;
	int priority;
	int round;
	int cpu_time;
	int need_time;
	int count;
	char state;
public:
	PCB(string name, int priority,	int round, int cpu_time, int need_time, int count, char state);
	bool operator < (PCB p){
		// cout << "hahahah";
		return (this -> round) < (p.round);
	}
};
	
PCB::PCB(string name, int priority,	int round, int cpu_time,
		int need_time, int count, char state)
{
	this -> name = name;
	this -> priority = priority;
	this -> round = round;
	this -> cpu_time = cpu_time;
	this -> need_time = need_time;
	this -> count = count;
	this -> state = state;
}

// bool PCB::opeator < (const PCB * p){
// 	return (this -> round) < (p -> round);
// }








#endif