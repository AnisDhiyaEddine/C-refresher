#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/types.h>

#define A sleep(3);

int main(int argc, char *argv[]){
    int i;
    int n = atoi(argv[1]);
    int p = atoi(argv[2]);

    if(p == 0){
        A;
        printf("output1\n");
        exit(0);
    }

    for(i=0;i<n;i++){
        if(fork() == 0){
            sprintf(argv[2],"%d",p-1);
            main(argc,argv); // Call the main again and again last child ops no fork state change during the excution ;)
            printf("output2\n");
            exit(0);
        }
    }

    while(wait(0) != -1){
        printf("output3\n");
        exit(0);
    }
}