// Nom: BOUDIAF
// Prénom: ANISDHIYAEDDINE
// Numéro Etudiant: 12015262


#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<pthread.h>

typedef struct argument_texte_s{
  char * texte;
  size_t taille_texte;
}argument_texte_t;


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
  argument_texte_t initialized = {texte, taille};
  return initialized;
}

argument_fichier_t *creer_argument_fichier(char *chemin){
  argument_fichier_t * args = malloc(sizeof(argument_fichier_t));
  args->chemin = chemin;
  args->resultat = 0;
  return args;
}

void liberer_argument_fichier(argument_fichier_t *args){
  args = NULL;
  free(args);
}
/***************************************** Exercice 3 *****************************************/

void * rechercher_texte(void *args){
  argument_texte_t *args = (void *)args;
}
/***************************************** Exercice 4 *****************************************/


/***************************************** Exercice 5 *****************************************/


/***************************************** Exercice 6 *****************************************/


int main(int argc, char ** argv){
  return EXIT_SUCCESS;
}
