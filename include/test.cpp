#include "PCB.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	PCB * a = new PCB("process_a", 1, 1, 1, 1, 1, 'a');
	PCB * b = new PCB("process_b", 1, 1, 1, 1, 1, 'b');
	cout << (*a < *b);
	return 0;
}
