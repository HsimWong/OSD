#include "PCB.h"
#include <iostream>
#include <queue>
using namespace std;

class Manager{
private:
	queue<PCB *> running;
	queue<PCB *> ready;
	queue<PCB *> finished;
	
public:
	Manager();
	~Manager();
	
};


int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}