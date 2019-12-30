#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

using std::string;
using std::to_string;
using std::cout;
using std::endl;

static int counter = 0;
static int max = 25;
static float timeout = 0.5;

void* counter1(void *arg);
void* counter2(void *arg);

int main() {
    pthread_t counter1_Thread;
    pthread_t counter2_Thread;

    pthread_create(&counter1_Thread, NULL, counter1, NULL);

    sleep(timeout);

    pthread_create(&counter2_Thread, NULL, counter2, NULL);

    pthread_join(counter1_Thread, NULL);
    pthread_join(counter2_Thread, NULL);

    cout << "Stopped counting, result: " + to_string(counter) << endl;
}

void* counter1(void *arg) {
    int i;
    int local;
    for (i = 0; i < max; i++) {
        local = counter;
        cout << "Counter 1 value: " + to_string(local) << endl;
        local++;
        counter = local;

        sleep(timeout);
    }
}

void* counter2(void *arg) {
    int i;
    int local;
    for (i = 0; i < max; i++) {
        local = counter;
        cout << "Counter 2 value: " + to_string(local) << endl;
        local--;
        counter = local;

        sleep(timeout);
    }
}
