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
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int CanalLectureS , CanalEcritureS;
static int CanalLectureEGB , CanalEcritureEGB;
static int CanalLecturePBP , CanalEcriturePBP;
static int CanalLectureABP , CanalEcritureABP;
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

static void initialisation ( )
{

	//Création du canal de communication Clavier->EntreeGastonBerger
		int canalEGB[2];
		pipe(canalEGB);
		CanalLectureEGB = canalEGB[0];
		CanalEcritureEGB = canalEGB[1];


	//Création du canal de communication Clavier->EntreeProfBlaisePascal
		int canalPBP[2];
		pipe(canalPBP);
		CanalLecturePBP = canalPBP[0];
		CanalEcriturePBP = canalPBP[1];

	//Création du canal de communication Clavier->EntreeProfBlaisePascal
		int canalABP[2];
		pipe(canalABP);
		CanalLectureABP = canalABP[0];
		CanalEcritureABP = canalABP[1];

	//Création du canal de communication Clavier->Sortie
		int canalS[2];
		pipe(canalS);
		CanalLectureS = canalS[0];
		CanalEcritureS = canalS[1];
}


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( void )
// Algorithme :
//
{

	pid_t clavierPid;
	pid_t heurePid;
	pid_t entreeABPPid, entreePBPPid, entreeGBPid;
	pid_t sortiePid;

		//--------------------------------------------------Initialisation

	InitialiserApplication( XTERM );
	initialisation();//Appel de la fonction d'initialisation de la tache


	if ( ( clavierPid = fork() ) == 0 )
	{
	//	close(canal[0]);//Fait dans Clavier
		Clavier(CanalLectureS,CanalEcritureS,CanalLectureEGB,CanalEcritureEGB,CanalLecturePBP,CanalEcriturePBP,CanalLectureABP,CanalEcritureABP); //Création de la tache fils Clavier
//		sleep(10);
	}
	else if( ( sortiePid = fork() ) == 0 )
	{
		//close(canalEGB[1]);
		Entree(CanalLectureS,CanalEcritureS);
		//close(canalEGB[0]);
	}
	else if( ( entreeGBPid = fork() ) == 0 )
	{
		//close(canalEGB[1]);
		Entree(CanalLectureEGB,CanalEcritureEGB);
		//close(canalEGB[0]);
	}
	else if( ( entreeABPPid = fork() ) == 0 )
	{
		//close(canalEGB[1]);
		Entree(CanalLectureABP,CanalEcritureABP);
		//close(canalEGB[0]);
	}
	else if( ( entreePBPPid = fork() ) == 0 )
	{
		//close(canalEGB[1]);
		Entree(CanalLecturePBP,CanalEcriturePBP);
		//close(canalEGB[0]);
	}
	else
	{
		//---------------------------------------------Phase Moteur
			heurePid = ActiverHeure();	//Création de la tache fils Heure

			//---------------------------------------------Destruction
			struct sigaction action;
			action.sa_handler = finHeure;
			sigemptyset ( &action.sa_mask );
			sigaction ( SIGUSR2, &action, NULL);

			waitpid ( clavierPid , NULL , 0 ); // Attente de la Fin de la tache Clavier
			kill ( heurePid , SIGUSR2 );
			waitpid ( heurePid , NULL , 0 );

				//Provoquer la mort des taches filles (Entree-Sortie)
				//Supprimer les canaux de communication


			TerminerApplication( true );
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
