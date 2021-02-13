#include<stdio.h>
#include<stdlib.h>




int main () {
  char x[11];

  printf("Dis moi un truc\n");
  scanf("%10s", x); 

  printf("Tu m'as dis: %s \n", x);
  
  return EXIT_SUCCESS;
}
