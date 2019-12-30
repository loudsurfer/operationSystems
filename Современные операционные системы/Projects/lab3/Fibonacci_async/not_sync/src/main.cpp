#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include "fib.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;
using std::to_string;

void* fibNumbers_Write(void *arg);
void* fibNumbers_Read(void *arg);

string filePath = "fibNumbers.txt";

int main()
{
  pthread_t fibNumbers_WriteThread;
  pthread_t fibNumbers_ReadThread;
  int writeStatus = pthread_create(&fibNumbers_WriteThread, NULL, fibNumbers_Write, NULL);

  if(writeStatus == 0){
    pthread_join(fibNumbers_WriteThread, NULL);
  }

  int readStatus = pthread_create(&fibNumbers_ReadThread, NULL, fibNumbers_Read, NULL);

  if(readStatus == 0){
    pthread_join(fibNumbers_ReadThread, NULL);
  }
}

void* fibNumbers_Write(void *arg){
  ofstream fibNumbers;
  fibNumbers.open(filePath);

  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

  int i = 0;

  if(fibNumbers.is_open()){
    while(i < 13){
      fibNumbers << Fib(i) << endl;
      cout << "Searching and writing " + to_string(i) + " fibonacci's number" << endl;

      sleep(1);
      i++;
    }
  }

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_testcancel();
}

void* fibNumbers_Read(void *arg){
  string fibNumberLine;
  ifstream fibNumbers(filePath);

  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

  if(fibNumbers.is_open()){
    while (getline(fibNumbers, fibNumberLine)){
      cout << fibNumberLine << endl;
    }
  }

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_testcancel();
}
