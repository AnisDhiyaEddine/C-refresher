#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


void *function(void *argv);

char **create_arguments(int n,int p){
char **args;
args = (char **)malloc(3*sizeof(char *));
args[0]= NULL;
args[1] = (char *)malloc(sizeof(int) *11);
sprintf(args[1],"%d",n);
args[2] = (char *)malloc(sizeof(int) * 11);
sprintf(args[2],"%d",p-1);
return args;
}


int main(int argc, char *argv[]){
    int i;
    pthread_t child;
    int n = atoi(argv[1]);
    int p = atoi(argv[2]);

    if(p == 0){
        printf("output1\n");
        pthread_exit(0);
    }

    for(i=0;i<n;i++){
        if(pthread_create(&child,NULL,function,create_arguments(n,p))){
            perror("error thread creation");
        }
    }

     
  printf("output3\n");
  pthread_exit(0);
}

void *function(void *argv){
    char ** args = (char **)argv;
    main(3,args);
    printf("output2\n");
    pthread_exit(0);
}