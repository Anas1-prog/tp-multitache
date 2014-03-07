
/*************************************************************************
                          Clavier  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par Amaury
*************************************************************************/

//---------- Réalisation de la tâche <Entree> (fichier Entree.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
//#include <iostream>
//#include <map>
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <stdlib.h>
//#include <signal.h>
//#include <sys/types.h>
//#include <sys/wait.h>

//------------------------------------------------------ Include personnel
#include "Entree.h"
//#include "Mere.h"
//#include "Outils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int canalLectureE;
static map<unsigned int, pid_t> voiturierEntree;
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


void entreeVoiture(int numSignal)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{

} //----- fin de entreeVoiture

void initialisation ( )
//Mode d'emploi
//
//Algo
//
{
	SetSignalHandler ( SIGUSR2 , destructionEntree ) ;
	SetSignalHandler ( SIGCHLD , entreeVoiture ) ;
}

void destructionEntree (int numSignal)
//Mode d'emploi
//Declenche par la reception du signal SIGUSR2
//Algorithme
//
{
	//Masquage du signal SIGCHLD
	SetSignalHandler(SIGCHLD, SIG_IGN);
	//TODO Kill tous les voituriers en cours
	exit(0);
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques


void Entree(int canal[2], TypeBarriere barriere)
{

	int lecture=0;
	char car;
	canalLectureE=canal[0];
	close(canal[1]);


	//---------------------------------------------------Initialisation
	initialisation();

	//---------------------------------------------------Phase Moteur


	for(;;)
	{
		lecture = read( canalLectureE, &car, sizeof( char ) );
		
		if ( lecture > 0 )
		{
			GarerVoiture(barriere);
		}
		else if (lecture == 0)
		{
			close(canalLectureE);
			exit(0);
		}
	}
}

