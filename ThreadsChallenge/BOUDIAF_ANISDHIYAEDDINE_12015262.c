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

#define nmrEtudiant 12015262
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
argument_texte_t creer_argument(char *texte, int taille){
  argument_texte_t initialized;
  initialized.taille_texte = taille;
  initialized.texte = malloc(sizeof(char) * taille);
  int i;
  for (i = 0; i < taille;i++){
    initialized.texte[i] = texte[i];
  }
   // strcpy(initialized.texte, (const char *)texte);
  return initialized;
}

argument_fichier_t *creer_argument_fichier(char *chemin){
  argument_fichier_t * args = malloc(sizeof(argument_fichier_t));
  args->chemin = malloc(sizeof(char) * strlen(chemin));
  strcpy(args->chemin, chemin);
  return args;
}

void liberer_argument_fichier(argument_fichier_t *args){
  args = NULL;
  free(args);
}
/***************************************** Exercice 3 *****************************************/

void * rechercher_texte(void *args){
  argument_texte_t *arg = (void *)args;
  int *found = malloc(sizeof(int));
  *found = 0;
  if (strstr(arg->texte, "12015262") != NULL)
  {
    *found = 1;
    return (void *)found;
  }
  pthread_exit((void *)found);
}
/***************************************** Exercice 4 *****************************************/
pthread_attr_t attributs_recherche_texte()
{
  pthread_attr_t *attr = malloc(sizeof(pthread_attr_t));
  pthread_attr_setstacksize(attr, PTHREAD_STACK_MIN);
  return *attr;
}

pthread_attr_t attributs_recherche_fichier()
{
  pthread_attr_t *attr = malloc(sizeof(pthread_attr_t));
  pthread_attr_setstacksize(attr,nmrEtudiant);
  return *attr;
}

    /***************************************** Exercice 5 *****************************************/
    void copie_fichier_chaine(char *chemin,char *chaine,long taille){
      if(taille > 1E7 )
        return;

      FILE *fp = fopen(chemin, "r");
      int i = 0;

      while(!feof(fp)){
        chaine[i] = fgetc(fp);
        i++;
      }
      i--;
      chaine[i] = '\0';
      fclose(fp);
    }

    void decouper(argument_texte_t tab[10],char *chaine,long length){
      int i, j,block = floor(length / 10) + 1;
      char *str = malloc(sizeof(char) * block);
      for (i = 0; i < 9; i++)
      {
        for (j = 0; j < block; j++) str[j] = chaine[j + block * i];
        tab[i] = creer_argument(str, block);
      }

      free(str);
      str = malloc(sizeof(char)*(length - block * 9));
      for (j = 0; j < length - block * 9; j++) str[j] = chaine[j - 1 + block * 9];
       tab[9] = creer_argument(str, (length - block * 9));
    }




    void *recherche_fichier(void * arg_fichier){

      argument_fichier_t arg = *(argument_fichier_t *)arg_fichier;

      printf("%s \n", arg.chemin);
      char *chaine = malloc(sizeof(char) * 1E6);
      copie_fichier_chaine(arg.chemin, chaine, taille_fichier(arg.chemin));
      argument_texte_t tab[10];
      decouper(tab, chaine, taille_fichier(arg.chemin));
      int i;
            pthread_t th[10];
      void *ret;
      pthread_attr_t attr = attributs_recherche_texte();
      for (i = 0; i < 10;i++){
        pthread_create(&th[i], &attr, rechercher_texte, (void *)&tab[i]);
      }

      for (i = 0; i < 10; i++)
      {
        pthread_join(th[i], &ret);
        if (**(int **)&ret == 1)
        {
         arg.resultat = '1';
        }
      }
      pthread_exit((void *)&arg);
    }

    /***************************************** Exercice 6 *****************************************/

    int main(int argc, char **argv)
{

  DIR *dir = opendir(argv[1]);
  int nbrDesFichiers = combien_de_fichiers(dir);
  printf("le nombre des fichier est %d\n", nbrDesFichiers);
  int i = 0;
  pthread_t *th = malloc(sizeof(pthread_t) * nbrDesFichiers);
  pthread_attr_t attr = attributs_recherche_fichier();
  argument_fichier_t *arg = malloc(sizeof(argument_fichier_t));
  struct dirent *contenu;
  while ((contenu = readdir(dir)) != NULL)
  {
    if (contenu->d_type == DT_REG)
    {

      arg->chemin = contenu->d_name;
      arg->resultat = '-';
      pthread_create(&th[i], &attr, recherche_fichier,creer_argument_fichier(arg->chemin));
      i++;
    }
   }

  void *ret;
  argument_fichier_t argument;
  for (i = 0; i < nbrDesFichiers; i++)
  {
    pthread_join(th[i], &ret);
    argument = *(argument_fichier_t *)ret;
    if (argument.resultat == '1')
      printf("le fichier %s contient mon numéro d'étudiant \n", argument.chemin);
  }
    return EXIT_SUCCESS;
}



