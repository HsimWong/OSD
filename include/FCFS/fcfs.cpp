#include <iostream>
using namespace std;
struct PCB{
    char name[10];      // Notation string of the process
    int prio;           // Priority of the process
    int round;
    int cputime;
    int needtime;
    int count;
    char state;
    struct node * next;
};

void tick(PCB * p){

}
