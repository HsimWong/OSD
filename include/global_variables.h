#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H 
// #ifndef timelet
#include <iostream>
#define INFINITY 65535
using namespace std;

int timelet;

void set_timelet(int l){
	timelet = l;
}

int get_timelet(){
	return timelet;
}

// #endif
#endif