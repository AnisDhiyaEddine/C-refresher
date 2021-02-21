// Nom: BOUDIAF
// Prénom:ANISDHIYAEDDINE
// Numéro Etudiant: 12015262


#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<pthread.h>
#include <limits.h> // PTHREAD_STACK_MIN
#include <math.h>
#include <unistd.h>

#define nbrEtudiant 12015262

typedef struct argument_texte_s
{
  char * texte;
  size_t taille_texte;
} argument_texte_t;

typedef struct argument_fichier_s{
  char * chemin;
  char resultat;
}argument_fichier_t;


/**
   Cette fonction renvoie la taille du fichier/répertoire dont le chemin est passé en argument.
   @param chemin est le chemin relatif ou absolu du fichier dont on souhaite connaître la taille.
   @result la taille du fichier/répertoire si le chemin est valide, 0 sinon.
 */
size_t taille_fichier(const char * chemin) {
    struct stat st; 

    if (stat(chemin, &st) == 0)
      return st.st_size;

    return 0; 
}

/**
   Cette fonction renvoie le nombre de fichiers contenu dans un répertoire.
   @requires dir != NULL, dir a déjà été ouvert avec la fonction opendir.
   @param dir est un répertoire
   @return le nombre de fichier contenu dans le répertoire. 
 */
size_t combien_de_fichiers(DIR * dir){
  struct dirent * contenu;
  size_t res = 0;
  while ((contenu = readdir(dir)) != NULL){
    if( contenu->d_type == DT_REG)
      res++;
  }
  rewinddir(dir);
  return res;
}



/***************************************** Exercice 2 *****************************************/

/**
   Cette fonction renvoie une nouvelle structure de type argument_text_t initialisé avec les parametres
   @requires stlen(texte) == taille > 0;
   @param texte est une chaine de caractère
   @param taille est un nombre qui represente la taille de la chaine de caractère
   @return une structure argument_text_t initialisé avec texte et taille 
 */
argument_texte_t creer_argument(char *texte, int taille){
  argument_texte_t initialized;
  initialized.taille_texte = taille;
  initialized.texte = malloc(sizeof(char) * taille);
  for (int i = 0; i < taille;i++){
    initialized.texte[i] = texte[i];
  }
  return initialized;
}

/**
   Cette fonction renvoie un pointeur vers une structure de type argument_fichier_t initialisé avec les parametres
   @requires chemin != NULL || "";
   @param chemin est un chaine de caractère qui represente le chemin de fichier
   @return un pointeur vers une structure argument_fichier_t initialisé avec le chemin de fichier
 */
argument_fichier_t *creer_argument_fichier(char *chemin){
  argument_fichier_t * args = malloc(sizeof(argument_fichier_t));
  args->resultat = '-';
  args->chemin = malloc(sizeof(char) * strlen(chemin));
  for (int i = 0; i < strlen(chemin);i++){
    args->chemin[i] = chemin[i];
  }
    return args;
}

/**
   Cette fonction libère la structure argument_fichier_t passé en argument
   @param args est un pointeur vers la structure argument_fichier_t
 */
void liberer_argument_fichier(argument_fichier_t *args){
  args->chemin = NULL;
  free(args);
}



/***************************************** Exercice 3 *****************************************/

/**
   Cette fonction recherche dans une chaine le nbrEtudiant codé en dur
   @requires args != NULL.
   @param args est un poineur vers argument_texte_t après le cast
   @return 1 si la chaine contient le numéro étudiant 0 sinon 
 */
void * rechercher_texte(void *args){
  argument_texte_t *arg = (void *)args;
  int *found = malloc(sizeof(int));
  *found = 0;
  if (strlen(arg->texte) >= 9){
    if (strstr(arg->texte, "12015262") != NULL)
      *found = 1;
  }

  pthread_exit((void *)found);
}


/***************************************** Exercice 4 *****************************************/

/**
   Cette fonction initialise les attributs d'un thread avec min stack size
   @return un pointeur vers une structure d'attribut initialisé
 */
pthread_attr_t attributs_recherche_texte()
{
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
  return attr;
}

/**
  Cette fonction initialise les attributs d'un thread avec le numéro d'étudiant
   @return un pointeur vers une structure d'attribut initialisé
 */
pthread_attr_t attributs_recherche_fichier()
{
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, nbrEtudiant);
  return attr;
}



    /***************************************** Exercice 5 *****************************************/

/**
   Cette fonction copie le contenu d'un fichier dans une chaine de caractères
   @requires chemin != NULL.
   @requires chaine != NULL.
   @requires taille <= 1E7, taille inférieur à 10Mo

   @param chemin est une chaine de caratctère qui represente le chemin vers le fichier à lire
   @param chaine est une chaine de caratctère qui va contenir le contenu de fichier
   @param taille est un nombre qui represente la taille de fichier
 */

void copie_fichier_chaine(char *chemin, char *chaine, long taille)
{
  if (taille > 1E7)
    return;

  FILE *fp = fopen(chemin, "r");
  int i = 0;

  while (!feof(fp))
  {
    chaine[i++] = fgetc(fp);
  }
  chaine[i--] = '\0';
  fclose(fp);
    }

    /**
   Cette fonction decoupe une chaine de caractère en 10 sous chaine égaux en taille sauf le dernier qui est légèrement plus petit
   @requires chaine != NULL.
   @requires length > 18.
   @param tab est un tableau de 10 structures argument_texte_t qui vont contenir les differentes parties de la chaine à decouper
   @param chaine est une chaine de caractère qu'on va découper
   @param length est un nombre qui represente la taille de la chaine à découper
 */

    void decouper(argument_texte_t tab[10], char *chaine, long length)
    {
      int i, j,block = floor(length / 10) + 1;
      char *str = malloc(sizeof(char) * block);
      for (i = 0; i < 9; i++)
      {
        for (j = 0; j < block; j++) str[j] = chaine[j + block * i];
        //strncat(str, chaine + block * i, block);
        tab[i] = creer_argument(str, block);
      }

      free(str);
      char *str1 = malloc(sizeof(char) * (length - block * 9));
      for (j = 0; j < length - block * 9; j++) str1[j] = chaine[j+ block * 9];
       tab[9] = creer_argument(str1, (length - block * 9));
      free(str1);
  }

  /**
   Cette fonction recherche dans un fichier l'existance d'un numéro étudiant codé en dur dans la fonction rechercher_texte
   @requires arg_fichier != NULL.
   @param arg_fichier est un pointeur après le cast vers une structure argument_fichier_t qui contient les informations nécessaire de fichier pour chercher le nbrEtudiant 
   @return arg casté pointeyur vers une structure argument_fichier_t qui contient un flag résultat positioné à '1' si le fichier contient le nbrEtudient '-' sinon
 */
  void *recherche_fichier(void *arg_fichier)
  {


    argument_fichier_t arg = *(argument_fichier_t *)arg_fichier;
    char *chaine = malloc(sizeof(char) * 1E7);
    argument_texte_t tab[10];
    int i;
    pthread_t *th = malloc(sizeof(pthread_t)*10);
    void *ret;
    pthread_attr_t attr = attributs_recherche_texte();

    copie_fichier_chaine(arg.chemin, chaine, taille_fichier(arg.chemin));
    decouper(tab, chaine, taille_fichier(arg.chemin));
    for (i = 0; i < 10; i++)
    {
      if(pthread_create(&th[i], &attr, rechercher_texte, (void *)&tab[i])){
        perror("error creation threads to operate on file slices");
        exit(EXIT_FAILURE);
      } 
    }

    for (i = 0; i < 10; i++)
    {
      pthread_join(th[i], &ret);
      if (*(int *)ret == 1)
      {
        arg.resultat = '1';
      }
    }

    
    free(ret);
    free(th);
    free((void *)chaine);
    for (i = 0; i < 10;i++){
      free((void *)tab[i].texte);
    }
    pthread_attr_destroy(&attr);
    pthread_exit(&arg);
    }



    /***************************************** Exercice 6 *****************************************/

    int main(int argc, char **argv)
{
  DIR *dir = opendir(argv[1]);
  int nbrDesFichiers = combien_de_fichiers(dir);
  int i = 0;
  void *ret;

  pthread_t *th = malloc(sizeof(pthread_t) * nbrDesFichiers);
  pthread_attr_t attr = attributs_recherche_fichier();
  argument_fichier_t argument, *arg = malloc(sizeof(argument_fichier_t));
  struct dirent *contenu;

  while ((contenu = readdir(dir)) != NULL)
  {
    if (contenu->d_type == DT_REG)
    {
      arg->chemin = contenu->d_name;
      arg->resultat = '-';
       if (pthread_create(&th[i], &attr, recherche_fichier,creer_argument_fichier(arg->chemin)))
      {
        perror("error creation threads to operate on files");
        exit(EXIT_FAILURE);
      } 
      i++;
    }
  }

   for (i = 0; i < nbrDesFichiers; i++)
  {
    pthread_join(th[i], &ret);
    argument = *(argument_fichier_t *)ret;
    if (argument.resultat == '1'){
      printf("le fichier %s contient mon numéro d'étudiant \n", argument.chemin);
    }
  
  }
 
    free(th);
    liberer_argument_fichier(arg);
  return EXIT_SUCCESS;
}

// gcc -Wall BOUDIAF_ANISDHIYAEDDINE_12015262.c -o main -lpthread
// valgrind --max-stackframe=12000000 --track-origins=yes ./main ./

