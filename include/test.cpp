#include "Queue.h"
#include "PCB.h"
#include "global_variables.h"
#include <iostream>
using namespace std;


int main(int argc, char const *argv[])
{
	set_timelet(1000);
	cout << get_timelet();
	return 0;
}