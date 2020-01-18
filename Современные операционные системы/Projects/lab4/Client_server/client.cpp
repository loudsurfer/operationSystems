#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <strings.h>
#include <fstream>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#define MAXLINE 128
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::to_string;


int main(int argc, char **argv) {
  int readfd = -1, writefd = -1;
  int number;
  string s;

while(1){
    cout << "Please, enter a number to be squared: " << endl;
    cin >> number;
    s = to_string(number);
    ssize_t n;

    char str[MAXLINE];
    strcpy(str, s.c_str());
  
//mkfifo именованый поток
// EEXIST файл уже существует
    if (mkfifo(FIFO2, FILE_MODE) == EEXIST) cout << " \n Pipes is exists" << endl;
  
  //O_WRONLY флаг того что файл открыт только для записи

    writefd = open(FIFO2, O_WRONLY);

    if ((writefd != -1)) {
      write(writefd, str, strlen(str));

      readfd = open(FIFO1, O_RDONLY);

      while ((n = read(readfd, str, MAXLINE)) > 0) {
        str[n] = 0;
        cout <<"Result: \""<<str<<"\""<<endl;

        break;
      }

      close(readfd);
      close(writefd);

    } else cout << "Can't open pipes..." <<endl;
  }
  return 1;
}
