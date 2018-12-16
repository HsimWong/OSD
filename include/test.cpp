#include <iostream>
#include "PCB.h"
#include "Manager.h"
#include <algorithm>
#include <queue>
using namespace std;

int main(int argc, char const *argv[]){
	Manager * mg = new Manager();
	mg ->manager_run_fcfs();
}