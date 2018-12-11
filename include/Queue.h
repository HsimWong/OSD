#ifndef QUEUE_H
#define QUEUE_H 
#include<iostream>
using namespace std;


class Queue{
private:
	PCB * head;
	PCB * tail;
	int capacity;
public:
	Queue(PCB * head);
	~Queue();
	bool notNull();
	bool push();
	bool pop();
	PCB * top();
	int get_capacity();
};

Queue::Queue(PCB * head){
	this -> head = head;
	this -> tail = head;
}

bool Queue:: push(PCB * new_node){
	this -> tail -> append(new_node)
	return true;
}

bool Queue::pop(){
	if(this -> notNull()){
		this -> head = this -> head -> next_node;
		this -> head -> ~PCB();
		return true;
	}
	else{
		cerr << "Error occured when pop the queue" << endl;
		return false;
	}
}




#endif