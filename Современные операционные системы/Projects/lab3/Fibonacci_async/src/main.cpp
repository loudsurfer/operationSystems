#include <iostream>
#include <fstream>
#include <semaphore.h>
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

sem_t fib_sem;
int fibSem_Value = 0;

int main()
{
  pthread_t fibNumbers_WriteThread, fibNumbers_ReadThread;

  int res = sem_init(&fib_sem, 0, 1);

  if (res != 0) {
    perror("Semaphore initialization failed");
    exit(EXIT_FAILURE);
  }

  int writeStatus = pthread_create(&fibNumbers_WriteThread, NULL, fibNumbers_Write, NULL);

  if(writeStatus != 0){
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }

  int readStatus = pthread_create(&fibNumbers_ReadThread, NULL, fibNumbers_Read, NULL);

  if(readStatus != 0){
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }

  pthread_join(fibNumbers_WriteThread, NULL);
  pthread_join(fibNumbers_ReadThread, NULL);

  sem_destroy(&fib_sem);
}

void* fibNumbers_Write(void *arg){
  sem_wait(&fib_sem);

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
  sem_post(&fib_sem);

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_testcancel();
}

void* fibNumbers_Read(void *arg){
  //sem_wait(&fib_sem);

  while(fibSem_Value <= 0){
    cout << "Reading attempt!" << endl;
    sleep(1);
    sem_getvalue(&fib_sem, &fibSem_Value);
  }

  string fibNumberLine;
  ifstream fibNumbers(filePath);

  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

  if(fibNumbers.is_open()){
    while (getline(fibNumbers, fibNumberLine)){
      cout << fibNumberLine << endl;
    }
  }
  sem_post(&fib_sem);

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_testcancel();
}
