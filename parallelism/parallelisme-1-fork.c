#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

//Demonstrate the main diffrence between threads and child processes created by fork


// Program that runs n copies of a command 
// ./run copiesNbr cmd args


void *run(void *arg){
//cmd + args
printf("running the program %s \n", ((char **)arg)[0]);
if(execv(((char **)arg)[0],((char **)arg))<0){
  perror("Erreur of execv");
  exit(-1);
}
exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
  int i, n;
  n = atoi(argv[1]);
  for (i = 0; i < n;i++){
    if(fork() == 0){
      run(argv + 2);
    }
  }
  printf("\n ");

  exit(EXIT_SUCCESS);
}