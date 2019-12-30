#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <strings.h>
#include <fstream>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <stdlib.h>
#include <string>
#define MAXLINE 128
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::to_string;

int main(int argc, char **argv) {
  int readfd = -1, writefd = -1;
  ssize_t n = 0;
  char str[MAXLINE];
  long result;

  unlink(FIFO1);
  unlink(FIFO2);

  if (mkfifo(FIFO1, FILE_MODE) == EEXIST) cout << " \n Pipes is exists" << endl;
  if (mkfifo(FIFO2, FILE_MODE) == EEXIST) cout << " \n Pipes is exists" << endl;

  while (1){
    readfd = open(FIFO2, O_RDONLY, 0);

    if (readfd != -1) {
      while ((n = read(readfd, str, MAXLINE)) > 0) {
        str[n] = 0;
        result = static_cast<int>(str[0]);

        break;
      }

      result = atoi(str);
      result *= result;
      string s = to_string(result);

      strcpy(str, s.c_str());

      writefd = open(FIFO1, O_WRONLY, 0);

      write(writefd, str, strlen(str));

      close(readfd);
      close(writefd);

      //break;
    }
    sleep(1);
  }
  return 1;
}
