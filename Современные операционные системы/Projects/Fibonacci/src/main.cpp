#include <iostream>
#include "fib.h"

using std::cout;
using std::endl;

int main()
{
  int i = 0;

  while(i < 13)
  {
    cout << Fib(i) << endl;
    i++;
  }
  return 0;
}
