#include "Manager.h"
#include "ProcessGen.h"
#include <iostream>
using namespace std;  

int main(int argc, char const *argv[])
{
      Manager * mg = new Manager();
      mg -> manager_run();
      return 0;
}
