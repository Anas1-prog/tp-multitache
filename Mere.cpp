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
#include <signal.h>
#include <stdio.h>
//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Clavier.h"
#include "Outils.h"
#include "Heure.h"
#include "Entree.h"
#include "Sortie.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int CanalS[2];
static int CanalGB[2];
static int CanalPBP[2];
static int CanalABP[2];
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



void SetSignalHandler ( int signalNumber, void (*handler) (int) )
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset ( &action.sa_mask );
	action.sa_flags = 0;
	sigaction ( signalNumber, &action, NULL );
} // Fin de SetSignalHandler


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc, const char * argv[] )
// Algorithme :
//
{

	system("ipcs > ipc_e.txt");
	pid_t clavierPid;
	pid_t heurePid;
	pid_t entreeABPPid, entreePBPPid, entreeGBPid;
	pid_t sortiePid;

		//--------------------------------------------------Initialisation

	InitialiserApplication( XTERM );

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
	//	close(canal[0]);//Fait dans Clavier
		Clavier(CanalS,CanalGB,CanalPBP,CanalABP); //Création de la tache fille Clavier
//		sleep(10);
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
			SetSignalHandler ( SIGUSR2, finHeure);
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

				//Supprimer les canaux de communication


			TerminerApplication( true );
			system("ipcs > ipc_s.txt");
			exit(0);
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
 *
 *
 *
 *
 *
 *
 */
