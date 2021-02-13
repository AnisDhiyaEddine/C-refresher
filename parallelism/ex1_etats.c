#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h> // fork et wait
#include<unistd.h> // fork 
#include <sys/wait.h> // wait




int main () {
  pid_t pid ; // pid_t est un entier.
  int wstatus;
  
  if( (pid = fork()) < 0)
    return EXIT_FAILURE;
 

  if ( pid == 0 ) {
    while(1);
  }
  else{
    wait(&wstatus);
  }
  
  return EXIT_SUCCESS;
}
