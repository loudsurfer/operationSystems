#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <fstream>
#include <stdio.h>
#include <error.h>
#include <string>
#include <unistd.h>

using std::cout;
using std::endl;
using std::to_string;

int full;
int stop = 2;
int count = 0;
const int bufferSize = 10;
int buffer[bufferSize];

pthread_mutex_t lock;
pthread_cond_t cond;

void *writer(void *);
void *reader(void *);

int main() {
  pthread_t writer_Thread;
  pthread_t reader_Thread;

  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&lock, NULL);

  pthread_create(&writer_Thread, NULL, writer, NULL);
  pthread_create(&reader_Thread, NULL, reader, NULL);

  while(count < stop){}

  if(pthread_cancel(writer_Thread)){
    perror("writer_Thread can't stop!");
    exit(EXIT_FAILURE);
  };

  if(pthread_cancel(reader_Thread)){
    perror("reader_Thread can't stop!");
    exit(EXIT_FAILURE);
  };

  pthread_join(writer_Thread, NULL);
  pthread_join(reader_Thread, NULL);

  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&lock);
}

void *writer(void *){
  while(1){
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    pthread_mutex_lock(&lock);

    while(full){
      pthread_cond_wait(&cond, &lock);
    }

    for(int i = 0; i < bufferSize; i++){
      buffer[i] = i << i;
      cout << "Writing to buffer value: " + to_string(buffer[i]) << endl;
    }

    full = 1;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    pthread_testcancel();
  }
  return NULL;
}

void *reader(void *){
  while (1){
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    pthread_mutex_lock(&lock);

    while (!full){
      pthread_cond_wait(&cond, &lock);
    }

    for(int i = 0; i < bufferSize; i++){
      cout << "Reading buffer: " + to_string(buffer[i]) << endl;
      buffer[i] = 0;
    }

    full = 0;
    count++;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    pthread_testcancel();
  }
  return NULL;
}
