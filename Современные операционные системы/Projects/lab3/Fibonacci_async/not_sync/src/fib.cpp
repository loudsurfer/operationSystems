#include "fib.h"

int Fib(int i)
{
  int value = 0;
  if(i < 1) return 0;
  if(i == 1) return 1;

  return Fib(i-1) + Fib(i - 2);
}
