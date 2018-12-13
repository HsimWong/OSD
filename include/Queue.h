#ifndef QUEUE_H
#define QUEUE_H 
#include<iostream>
#include "PCB.h"
using namespace std;


class Queue{
private:
	PCB * head;
	PCB * tail;
	PCB * buff;
	int capacity;
public:
	Queue();
	Queue(PCB * head);
	~Queue();
	bool isEmpty();
	bool push(PCB * new_node);
	bool pop();
	PCB * top();
	int get_capacity();
};

Queue::Queue(){
	this -> buff = this -> head = this -> tail = new PCB("NULL",0,0,0);
	this -> tail -> append(this -> head);
	this -> capacity = 0;
}

Queue::Queue(PCB * head){
	this -> head = this -> buff = this -> tail = head;
	this -> tail -> append(this -> head);
	this -> capacity = 1;
	return;
}

bool Queue :: isEmpty(){
	return (this -> get_capacity() == 0);
}

bool Queue:: push(PCB * new_node){
	if(this -> capacity == 0){
		this -> head = this -> tail = new_node;
		this -> tail -> append(this -> head);
	}
	else{
		this -> tail -> append(new_node);
		this -> tail = new_node;
	}
	this -> capacity ++;
	return true;
}

bool Queue::pop(){
	if(this -> isEmpty()){
		cerr << "Error occured when pop the queue" << endl;
		return false;
	}
	else{
		PCB * temp = this -> head;
		this -> head = this -> head -> next_node;
		this -> tail -> append(this -> head);
		this -> capacity --;
		delete temp;
		return true;
	}
}

PCB * Queue::top(){
	if(this -> isEmpty()){
		cerr << "No top PCB found, the queue is empty";
		return NULL;
	}
	else{
		return this -> head; 
	}
}

int Queue::get_capacity(){
	return (this -> capacity);
}

#endif