#include <iostream>
#include "PCB.h"
#include <algorithm>
#include <queue>
using namespace std;

int main(){
      // priority_queue<PCB *> * a = new priority_queue<PCB *>();
      PCB * proa = new PCB("proa", 1, 1, 100);
      PCB * proc = new PCB("proc", 1, 1, 211);
      
      PCB * prob = new PCB("prob", 1, 1, 12);
     cout << (*proa < *prob);
}