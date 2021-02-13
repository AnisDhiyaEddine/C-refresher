/**
 * ----------------------------------------------------
 * Démonstration de l'utilisation de la libsched.
 * ----------------------------------------------------
 *
 * Utilisation de la politique FIFO en mode BATCH
 *
 * Auteur : Jean-Baptiste Voron (jean-baptiste.voron@lip6.fr)
 * Date   : 26/09/2008
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


/* Description d'un processus Moyen */
void ProcMoyen(int *pid){
	long i;

	for (i = 0; i < 5E7; i++)
		if (i % (long)4E6 == 0)
			printf("   Proc. Moy%d - %ld\n", *pid, i);
	printf("############ FIN Moy %d\n\n", *pid);
}

/* Fonction principale */
int main (int argc, char *argv[]) {
	int i;
	int *j;

	// Création des processus courts
	for (i = 0; i < 2; i++)
	{
		j = (int *)malloc(sizeof(int));
		*j = i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcCourt, (void *)j, 10);
	}

	for (i = 0; i < 2; i++)
	{
		j = (int *)malloc(sizeof(int));
		*j = i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcMoyen, (void *)j, 50);
	}

	
	// Créeation des processus longs
	for  (i = 0; i < 2; i++) {
		j = (int *) malloc(sizeof(int));
		*j= i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcLong,(void *)j, 100);
	}
	

	// Parametrage de l'ordonnanceur
	SchedParam(BATCH, 0, NULL);

	// Lancer l'ordonnanceur en mode verbeux
	sched(1);	

	// Imprimer les statistiques
	PrintStat();

	return EXIT_SUCCESS;
}
