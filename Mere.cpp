/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par kantoine
*************************************************************************/

//---------- Réalisation de la tâche <Mere> (fichier Mere.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <stdio.h>
#include <fstream>
//------------------------------------------------------ Include personnel
#include "Mere.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
#define CHMOD_MPREAD 400
#define CHMOD_MPWRITE 200
#define CHMOD_SEMREAD 400
#define CHMOD_SEMWRITE 200
#define CHEMIN "Semaphore"
#define CLEFS 3




//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int CanalS[2];
static int CanalGB[2];
static int CanalPBP[2];
static int CanalABP[2];
static pid_t clavierPid;
static pid_t heurePid;
static pid_t entreeABPPid, entreePBPPid, entreeGBPid;
static pid_t sortiePid;
static int semId;
int const CLEF = ftok ( CHEMIN, CLEFS );

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom
void finHeure ( int noSignal )
{
	if ( noSignal == SIGUSR2 )
	{
		exit(0);
	}
}


void destructionMere(int signal)
{
	if ( signal == SIGINT)
	{
		Handler ( SIGUSR2, finHeure);

		waitpid ( clavierPid , NULL , 0 ); // Attente de la Fin de la tache Clavier
		kill ( heurePid , SIGUSR2 );
		waitpid ( heurePid , NULL , 0 );
		kill ( sortiePid , SIGUSR2 );
		waitpid( sortiePid , NULL , 0 );
		kill ( entreeGBPid , SIGUSR2 );
		waitpid( entreeGBPid , NULL , 0 );
		kill ( entreeABPPid , SIGUSR2 );
		waitpid( entreeABPPid , NULL , 0 );
		kill ( entreePBPPid , SIGUSR2 );
		waitpid( entreePBPPid , NULL , 0 );

		//Suppression de la memoire partagee
		int memoirePartagee = shmget( CLEF, sizeof(EtatParking),IPC_EXCL);
		shmctl( memoirePartagee,IPC_RMID,0);
		//Suppression de la semaphore d'exclusion mutuelle
		semId = semget ( CLEF,1,IPC_EXCL);
		semctl(semId,0,IPC_RMID,0);
		//Libere les canaux de communication
		close(CanalS[0]);
		close(CanalS[1]);
		close(CanalGB[0]);
		close(CanalGB[1]);
		close(CanalABP[0]);
		close(CanalABP[1]);
		close(CanalPBP[0]);
		close(CanalPBP[1]);


		TerminerApplication( true );
		exit(0);
	}
}
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc, const char * argv[] )
// Algorithme :
//
{
		//--------------------------------------------------Initialisation

	InitialiserApplication( XTERM );
	Handler ( SIGINT, destructionMere );
	//Mise en place de la mémoire partagée
	int memoirePartagee = shmget ( CLEF, sizeof(EtatParking), (IPC_CREAT|IPC_EXCL|CHMOD_MPREAD|CHMOD_MPWRITE) );


	//Mise en place du Mutex
	semId = semget ( CLEF, 1, (IPC_CREAT|IPC_EXCL|CHMOD_SEMREAD|CHMOD_SEMWRITE) );

	//récupere la mémoire partagée
	EtatParking  * etat = (EtatParking *)shmat( memoirePartagee, NULL,0);
	etat->placeLibres=NB_PLACES;
	etat->nombreRequetes=0;
	shmdt ( etat );//Libère la mémoire

	//Libere le mutex
	semaphore(CLEF,1);

	//Création du canal de communication Clavier->EntreeGastonBerger
	pipe(CanalGB);
	//Création du canal de communication Clavier->EntreeProfBlaisePascal
	pipe(CanalPBP);
	//Création du canal de communication Clavier->EntreeProfBlaisePascal
	pipe(CanalABP);
	//Création du canal de communication Clavier->Sortie
	pipe(CanalS);


	if ( ( clavierPid = fork() ) == 0 )
	{
		Clavier(CanalS,CanalGB,CanalPBP,CanalABP); //Création de la tache fille Clavier
	}
	else if( ( entreeGBPid = fork() ) == 0 )
	{
		Entree(CanalGB,ENTREE_GASTON_BERGER);
	}
	else if( ( entreeABPPid = fork() ) == 0 )
	{
		Entree(CanalABP,AUTRE_BLAISE_PASCAL);
	}
	else if( ( entreePBPPid = fork() ) == 0 )
	{
		Entree(CanalPBP,PROF_BLAISE_PASCAL);
	}
	else if( ( sortiePid = fork() ) == 0 )
	{
		Sortie(CanalS);
	}
	else
	{
		//---------------------------------------------Phase Moteur
			heurePid = ActiverHeure();	//Création de la tache fils Heure

			//---------------------------------------------Destruction
			Handler ( SIGUSR2, finHeure);

			destructionMere(SIGINT);
		}
}



/*Etape de developpement :
 *
 * - Affichage des voitures aux différentes entrées : communication de la tache clavier avec l'entree
 * concernée
 *
 * - Entrees de voitures fonctionnelles : communication de la tache clavier avec l'entree
 * concernée pour faire entrer une voiture dans le parking
 *
 * - Sortie des vehicules fonctionnelle
 *
 * -Memoire partagéé mise en place
 * -Semaphore d'exclusion mutuelle mise en place
 * -Creation d'une fonction pour agir sur la semaphore : semaphore(int clef, short semOp)
 * -Initialisation de la mémoire à NB_PLACES libres dans mère
 * -Affichage des voitures qui sont entrées dans le parking
 * -Effacement de l'affichage des voitures qui sortent du parking
 *
 *
 * -Creation de requetes d'entree par les Entrées + Affichage des requetes.
 *
 * -Comparaison des requetes par la sortie et envoie du signal à l'entrée qui fait rentrer une voiture
 *
 *	-TODO Fin anormale (CTRL-C) tuer les process proprement
 *
 *
 */
 
