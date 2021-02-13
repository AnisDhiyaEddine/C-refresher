/**
 * -------------------------------------------------------------------
 * TP3 ASR : Politique d'ordonnancement Multi-Level Round Robin (RR).
 * -------------------------------------------------------------------
 *
 * Exercice 4
 * Auteur :
 * Date   :
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

/* Utilisation de la bibliotheque LIBSCHED */
#include "sched.h"

void ProcLongFork(int *);
void ProcLong(int *);
void ProcMoyen(int *);
void ProcCourt(int *);

/* Description d'un processus LONG+FORK */
void ProcLongFork(int *pid) {
	long i;
	int* j;

	for (i=0;i<5E8;i++) {
		if (i%(long)4E6 == 0) 
			printf("   Proc. LongFork%d - %ld\n",*pid, i);
		if (i%(long)1E8 == 0) {
			j = (int *) malloc(sizeof(int));
			*j= *pid + ((i/(long)1E8)+1) * 20;
			printf(" !! Nouveau Processus Long ! %d\n", *j);
			CreateProc((function_t)ProcLong,(void *)j, 100);
		}
	}
	printf("############ FIN LONGFORK %d\n\n", *pid );
}

/* Description d'un processus LONG */
void ProcLong(int *pid) {
	long i;

	for (i=0;i<5E8;i++)
		if (i%(long)4E6 == 0) 
		printf("   Proc. Long%d - %ld\n",*pid, i);
	printf("############ FIN LONG %d\n\n", *pid);
}

/* Description d'un processus MOYEN */
void ProcMoyen(int *pid) {
	long i;

	for (i=0;i<1E8;i++)
		if (i%(long)4E6 == 0) 
		printf("   Proc. Moyen%d - %ld\n",*pid, i);
	printf("############ FIN MOYEN %d\n\n", *pid);
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

int MLRRElect(void) {
	int elu;
	
	/**
	 *
	 * A VOUS DE JOUER !
	 * Objectif : Ecrire un algorithme qui choisisse le processus le principe du Tourniquet Multi Niveaux
	 *
	 **/
	
	return elu;
}


/* Fonction principale */
int main (int argc, char *argv[]) {
	int i;
	int *j;  

	// Création de 2 processus longs + fork
	for  (i = 0; i < 2; i++) {
		j = (int *) malloc(sizeof(int));
		*j= i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcLongFork,(void *)j, 150);
	}

	// Création de 3 processus longs
	for  (i = 0; i < 3; i++) {
		j = (int *) malloc(sizeof(int));
		*j= i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcLong,(void *)j, 100);
	}
	
	// Création de 3 processus moyens
	for  (i = 0; i < 3; i++) {
		j = (int *) malloc(sizeof(int));
		*j= i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcMoyen,(void *)j, 50);
	}

	// Création de 3 processus courts
	for  (i = 0; i < 3; i++) {
		j = (int *) malloc(sizeof(int));
		*j= i;
		// Ajout du processus dans la table des processus
		CreateProc((function_t)ProcCourt,(void *)j, 10);
	}

	// Parametrage de l'ordonnanceur
	// L'ordonnanceur utilise votre politique MLRR en mode TEMPS PARTAGE
	SchedParam(NEW, 1, MLRRElect);
	//SchedParam(NEW, 2, RRElect);
	//SchedParam(NEW, 3, RRElect);

	sched(1); // Lancer l'ordonnanceur en mode verbeux
	PrintStat(); // Imprimer les statistiques

	return EXIT_SUCCESS;
}
