#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "utils.c"

double * strassen1(double *A, double *B, int);
double *strassen2(double *A, double *B, int);


/************************************************************************/
int main ()
{
  double *A;
  double *B;
  double *C;
  double *D;

  int N =4;  /* dimension de la matrice : N puissance de 2 */

  clock_t debut, fin;
  double t;

  srand(time(NULL));

  A = creer_matrice(N);
  B = creer_matrice(N);


/*   remplisage_aleatoire(A, N);
  remplisage_aleatoire(B, N);
 */

  remplirABHard(A, B, N);
  /***************************/

  debut = clock();
  C = strassen2 (A, B, N); 
  fin = clock();

  
  /* mettre en commentaires une fois la fonction strassen soit correcte */
//  printf("\n Résultat Strassen : \n"); afficher_matrice (C, N); 
  /**********************/

  t = ((double) fin - debut)/CLOCKS_PER_SEC;
//  printf("\nLe temps d'exécution de l'algorithme de Strassen est : %.10f seconds\n", t);

  debut = clock();
  D = algo_naif (A, B, N);
  fin = clock();

  /* mettre en commentaires une fois la fonction strassen soit correcte */
  printf("\n Résultat classique : \n"); afficher_matrice (C, N); 
  /***********************/
 
  t = ((double) fin - debut)/CLOCKS_PER_SEC;
 // printf("\nLe temps d'exécution de l'algorithme naif est : %.10f seconds\n", t);

  liberer_memoire(A); liberer_memoire(B); 
  liberer_memoire(C); liberer_memoire(D); 
 return EXIT_SUCCESS;
}


/************************************************************************/

double * strassen1(double *A,double *B,int  n){
  int pui = log2(n) + 1;
  int taille = pow(2, pui);
  double *A_ = creer_matrice(taille);
  double *B_ = creer_matrice(taille);
  double *C_ = creer_matrice(taille);
  double *resultat = creer_matrice(n);

  composer_matrices(A_, taille, A, n, 0, 0);
  composer_matrices(B_, taille, B, n, 0, 0);
  C_ = strassen(A_, B_, taille);
  resultat = sous_matrice(C_, 0, 0, taille, n);
  return resultat;
}

/************************************************************************/

double *strassen2(double *A, double *B, int n)
{
  // cas de base n est une puissance de deux
  int pui = log2(n);
  if(pow(2,pui) == n){
    return strassen(A, B, n);
  }

  // cas générale
  double *A_ = creer_matrice(n - 1);
  double *B_ = creer_matrice(n - 1);
  double *C_ = creer_matrice(n - 1);
  double *C = creer_matrice(n);
  int i, j;
  A_ = sous_matrice(A, 0, 0, n, n - 1);
  B_ = sous_matrice(B, 0, 0, n, n - 1);
  C_ = strassen2(A_, B_, n - 1);
  double temp = 0;
  composer_matrices(C, n, C_, n - 1, 0, 0);
  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - 1;j++){
      C[i * n + j] = C_[i * (n-1) + j] + A[n * i + n - 1] * B[n*(n - 1) + j];
    }
  }


  // Le calcul du nième ligne de C
  for (j = 0; j < n;j++){
    temp = 0;
    for (i = 0; i < n - 1;i++){
      temp += A[n * (n - 1) + i] * B[n * i + j];
    }
    C[n * (n - 1) + j] = temp;
  }

  // Le calcul de nième collone de C
  for (i = 0; i < n-1; i++)
  {
    temp = 0;
    for (j = 0; j < n - 1; j++)
    {
      temp += A[i * n + j] * B[j * n + n - 1];
    }
    C[n * i + n - 1] = temp;
  }

  return C;
}

/************************************************************************/

