#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double * creer_matrice (int);
void    remplisage_aleatoire (double *, int);
void    afficher_matrice (double *M, int);
void    liberer_memoire(double * M);
double * sous_matrice (double * M, int, int, int, int);
void    addition_matrices (double * X, double *Y, double * R, int);
void    soustraction_matrices (double * X, double *Y, double * R, int);
void    composer_matrices(double * C, int, double *T1, int, int, int);
double * algo_naif (double *A, double * B, int);
double * strassen (double * A, double * B, int);

/************************************************************************/
int main ()
{
  double *A;
  double *B;
  double *C;
  double *D;

  int N = 4;  /* dimension de la matrice : N puissance de 2 */

  clock_t debut, fin;
  double t;

  srand(time(NULL));

  A = creer_matrice(N);
  B = creer_matrice(N);

  /* remplisage de A. Mettre en comentaires dès que les fonctions soient correctes */

  A[0*N + 0] = 2.0; A[0*N + 1] = 3.0; A[0*N + 2] = 4.0; A[0*N + 3] = 4.0; 
  A[1*N + 0] = 2.0; A[1*N + 1] = 6.0; A[1*N + 2] = 3.0; A[1*N + 3] = 7.0; 
  A[2*N + 0] = 4.0; A[2*N + 1] = 8.0; A[2*N + 2] = 2.0; A[2*N + 3] = 9.0; 
  A[3*N + 0] = 9.0; A[3*N + 1] = 6.0; A[3*N + 2] = 5.0; A[3*N + 3] = 8.0; 

  /* remplisage de B. Mettre en comentaires dès que les fonctions soient correctes  */

  B[0*N + 0] = 9.0; B[0*N + 1] = 2.0; B[0*N + 2] = 4.0; B[0*N + 3] = 2.0; 
  B[1*N + 0] = 3.0; B[1*N + 1] = 5.0; B[1*N + 2] = 2.0; B[1*N + 3] = 6.0; 
  B[2*N + 0] = 1.0; B[2*N + 1] = 7.0; B[2*N + 2] = 8.0; B[2*N + 3] = 1.0; 
  B[3*N + 0] = 4.0; B[3*N + 1] = 3.0; B[3*N + 2] = 3.0; B[3*N + 3] = 4.0; 

  /* remplisage aleatoire */

  /* code a utiliser une fois qu'on est sûr que les fonctions sont correctes */
  
  /*
  remplisage_aleatoire (A, N);
  remplisage_aleatoire (B, N); 
  */
  

  /* code à utiliser seulement pour faire des test. Apres, le mettre en comentaires */

  printf("\n A = \n"); afficher_matrice (A, N);
  printf("\n B = \n"); afficher_matrice (B, N); 
 
  /***************************/

  debut = clock();
  C = strassen (A, B, N); 
  fin = clock();

  
  /* mettre en commentaires une fois la fonction strassen soit correcte */
  printf("\n Résultat Strassen : \n"); afficher_matrice (C, N); 
  /**********************/

  t = ((double) fin - debut)/CLOCKS_PER_SEC;
  printf("\nLe temps d'exécution de l'algorithme de Strassen est : %.10f seconds\n", t);

  debut = clock();
  D = algo_naif (A, B, N);
  fin = clock();

  /* mettre en commentaires une fois la fonction strassen soit correcte */
  printf("\n Résultat clssique : \n"); afficher_matrice (D, N); 
  /***********************/
 
  t = ((double) fin - debut)/CLOCKS_PER_SEC;
  printf("\nLe temps d'exécution de l'algorithme naif est : %.10f seconds\n", t);

  liberer_memoire(A); liberer_memoire(B); 
  liberer_memoire(C); liberer_memoire(D); 
 return EXIT_SUCCESS;
}

/************************************************************************/

double * creer_matrice (int n)
{
  double * T = (double *) malloc (n*n*sizeof(double));
  return(T);
}

/************************************************************************/

void afficher_matrice (double * M, int n)
{
  int i,j;

  printf("\n");
  for (i=0; i < n; i++)
  {
    for (j=0; j < n; j++)
      printf("%.2f ",M[i*n + j]);
    printf("\n");
  }
}

/************************************************************************/

void liberer_memoire(double * M)
{
   free(M);
}

/************************************************************************/

double * sous_matrice (double * M, int l, int c, int n, int n2)
{
  double *S = creer_matrice (n2);
  int i,j;

  for (i=0; i<n2; i++)
    for (j=0; j<n2; j++)
       S[i*n2 + j] = M[(i + l*n2)*n + (j + c*n2)];
  return (S);
}

/************************************************************************/

void addition_matrices (double * X, double *Y, double * R, int n)
{
  int i,j;

  for (i=0; i<n; i++)
   for (j=0; j<n; j++)
     R[i*n + j] = X[i*n + j] + Y[i*n + j];
}

/************************************************************************/

void soustraction_matrices (double * X, double *Y, double * R, int n)
{
  int i,j;

  for (i=0; i<n; i++)
   for (j=0; j<n; j++)
     R[i*n + j] = X[i*n + j] - Y[i*n + j];
}

/************************************************************************/

void composer_matrices(double * C, int n, double *T, int n2, int l, int c)
{
  int i,j;

  for (i=0; i < n2; i++)
    for (j=0; j < n2; j++)
       C[(i + l*n2)*n + (j + c*n2)] = T[i*n2 + j];
}

/************************************************************************/

void remplisage_aleatoire (double * M, int n)
{

  int i,j;

  for (i=0; i<n; i++)
   for (j=0; j<n; j++)
    M[i*n + j] = rand();
}

/************************************************************************/

double * algo_naif (double * A, double * B, int n)
{
  double * X = creer_matrice(n);
  int i,j,k;

  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
    {
      X[i*n + j] = A[i*n]*B[j];
      for (k=1; k<n; k++)
        X[i*n + j] = X[i*n + j] + (A[i*n + k]*B[k*n + j]);
    }

  return X;
}

/************************************************************************/

double * strassen (double * A, double * B, int n)
{
  double * C = creer_matrice(n);


  if (n == 2) 
  {
     double p1,p2,p3,p4,p5,p6,p7;

     p1 = (A[0*n + 0] + A[1*n + 1])*(B[0*n + 0] + B[1*n + 1]);  /* (a11 + a22)*(b11 + b22) */
     p2 = (A[1*n + 0] + A[1*n + 1])*(B[0*n + 0]);               /* (a21 + a22)*(b11) */
     p3 = (A[0*n + 0])*(B[0*n + 1] - B[1*n + 1]);               /* (a11)*(b12 - b22) */
     p4 = (A[1*n + 1])*(B[1*n + 0] - B[0*n + 0]);               /* (a22)*(b21 - b11) */
     p5 = (A[0*n + 0] + A[0*n + 1])*(B[1*n + 1]);               /* (a11 + a12)*(b22) */
     p6 = (A[1*n + 0] - A[0*n + 0])*(B[0*n + 0] + B[0*n + 1]);  /* (a21 - a11)*(b11 + b12) */
     p7 = (A[0*n + 1] - A[1*n + 1])*(B[1*n + 0] + B[1*n + 1]);  /* (a12 - a22)*(b21 + b22) */
     
     C[0*n + 0] = p1 + p4 - p5 + p7;
     C[0*n + 1] = p3 + p5;
     C[1*n + 0] = p2 + p4;
     C[1*n + 1] = p1 - p2 + p3 + p6;
  }
  else
  {
     int n2 = n/2;
     double *A11; double * A12; double * A21; double * A22;
     double *B11; double * B12; double * B21; double * B22;

     double *P1; double *P2; double *P3; double *P4; double *P5; double *P6; double *P7;

     double * T1 = creer_matrice(n2); 
     double * T2 = creer_matrice(n2); /* matrices auxlieres */

     A11 = sous_matrice (A, 0, 0, n, n2);
     A12 = sous_matrice (A, 0, 1, n, n2);
     A21 = sous_matrice (A, 1, 0, n, n2);
     A22 = sous_matrice (A, 1, 1, n, n2);

     B11 = sous_matrice (B, 0, 0, n, n2);
     B12 = sous_matrice (B, 0, 1, n, n2);
     B21 = sous_matrice (B, 1, 0, n, n2);
     B22 = sous_matrice (B, 1, 1, n, n2);

     addition_matrices(A11, A22, T1, n2); addition_matrices(B11, B22, T2, n2);
     P1 = strassen (T1, T2, n2);

     addition_matrices(A21,A22, T1, n2);
     P2 = strassen (T1, B11, n2);

     soustraction_matrices (B12, B22, T1, n2);
     P3 = strassen (A11, T1, n2);

     soustraction_matrices (B21, B11, T1, n2);
     P4 = strassen (A22, T1, n2);

     addition_matrices(A11,A12, T1, n2);
     P5 = strassen (T1, B22, n2);

     soustraction_matrices(A21, A11, T1, n2); addition_matrices(B11, B12, T2, n2);
     P6 = strassen (T1, T2, n2);

     soustraction_matrices(A12, A22, T1, n2); addition_matrices(B21, B22, T2, n2);
     P7 = strassen (T1, T2, n2);

     addition_matrices(P1, P4, T1, n2); soustraction_matrices(T1, P5, T2, n2);
     addition_matrices(T2, P7, T1, n2); composer_matrices(C,n,T1,n2,0,0);

     addition_matrices(P3, P5, T1, n2); composer_matrices(C,n,T1,n2,0,1);

     addition_matrices(P2, P4, T1, n2); composer_matrices(C,n,T1,n2,1,0);

     soustraction_matrices(P1, P2, T1, n2); addition_matrices(T1, P3, T2, n2);
     addition_matrices(T2, P6, T1, n2); composer_matrices(C,n,T1,n2,1,1);
     
     liberer_memoire(A11); liberer_memoire(A12); liberer_memoire(A21); liberer_memoire(A22);
     liberer_memoire(B11); liberer_memoire(B12); liberer_memoire(B21); liberer_memoire(B22);
     liberer_memoire(P1);  liberer_memoire(P2);  liberer_memoire(P3);  liberer_memoire(P4);
     liberer_memoire(P5);  liberer_memoire(P6);  liberer_memoire(P7);  
     liberer_memoire(T1);  liberer_memoire(T2);
  } 
  return (C); 
}
