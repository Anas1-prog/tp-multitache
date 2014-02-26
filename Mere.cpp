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
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
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
static void finHeure ( int noSignal )
{
	if ( noSignal == SIGUSR2 )
	{
		exit(0);
	}
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( void )
// Algorithme :
//
{
	pid_t noFils1;
	pid_t noFils2;
	InitialiserApplication( XTERM );
	if ( ( noFils1 = fork() ) == 0 )
	{
		Clavier(); //Création de la tache fils Clavier
//		sleep(10);
	}
	else
	{
		struct sigaction action;
		action.sa_handler = finHeure;
		sigemptyset ( &action.sa_mask );
		sigaction ( SIGUSR2, &action, NULL);
		noFils2 = ActiverHeure();	//Création de la tache fils Heure
		waitpid ( noFils1 , NULL , 0 ); // Attente de la Fin de la tache Clavier
		kill ( noFils2 , SIGUSR2 );
		waitpid ( noFils2 , NULL , 0 );
		TerminerApplication( true );
		exit(0);
	}
} //----- fin de Nom
