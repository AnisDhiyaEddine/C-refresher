/**
 * ----------------------------------------------------
 * TP3 ASR : Politique d'ordonnancement ALEATOIRE.
 * ----------------------------------------------------
 *
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

/* Utilisation de la bibliotheque LIBSCHED */
#include "sched.h"

void ProcLong(int *);
void ProcCourt(int *);

/* Description d'un processus LONG */
void ProcLong(int *pid) {
	long i;

	for (i=0;i<1E8;i++)
		if (i%(long)4E6 == 0) 
		printf("   Proc. Long%d - %ld\n",*pid, i);
	printf("############ FIN LONG %d\n\n", *pid);
}

/* Description d'un processus COURT */
void ProcCourt(int *pid) {
	long i;

	for (i=0;i<1E7;i++)
		if (i%(long)4E6 == 0) 
		printf("   Proc. Court%d - %ld\n",*pid, i);
	printf("############ FIN COURT %d\n\n", *pid);
}


// --------------------------------------------------
// DEFINITION DE LA POLITIQUE D'ORDONNANCEMENT
// --------------------------------------------------

int RandomElect(void) {
	int elu;

	do{
		elu = (int)random() % MAXPROC;
	} while (Tproc[elu].flag != RUN);

	/**
	 *
	 * A VOUS DE JOUER !
	 * Objectif : Ecrire un algorithme qui choisisse au hasard un processus dans TProc
	 *
	 **/

	return elu;
}


/* Fonction principale */
int main (int argc, char *argv[]) {
	int i;
	int *j;  

	// Création de 5 processus longs
	for  (i = 0; i < 5; i++) {
		j = (int *) malloc(sizeof(int));
		*j= i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcLong,(void *)j, 100);
	}

	// Création de 10 processus courts
	for  (i = 0; i < 10; i++) {
		j = (int *) malloc(sizeof(int));
		*j= i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcCourt,(void *)j, 10);
	}

	// Parametrage de l'ordonnanceur
	// L'ordonnanceur utilise votre politique RANDOM en mode BATCH
	SchedParam(NEW, 0, RandomElect);

	sched(1); // Lancer l'ordonnanceur en mode verbeux
	PrintStat(); // Imprimer les statistiques

	return EXIT_SUCCESS;
}
