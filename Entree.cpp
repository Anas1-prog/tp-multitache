
/*************************************************************************
                          Clavier  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par Amaury
*************************************************************************/

//---------- Réalisation de la tâche <Entree> (fichier Entree.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Entree.h"
#include "Mere.h"

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


static void entreeVoiture(int numSignal)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{

} //----- fin de entreeVoiture

static void initialisation ( )
//Mode d'emploi
//
//Algo
//
{
	SetSignalHandler ( SIGUSR2 , destruction ) ;
	SetSignalHandler ( SIGCHLD , entreeVoiture ) ;
}

static void destruction ()
//Mode d'emploi
//Declenche par la reception du signal SIGUSR2
//Algorithme
//
{
	//Masquage du signal
	SetSignalHandler(SIGCHLD, SIG_IGN);

	//Kill tous les voituriers en cours


}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Entree(int CanalL,int CanalE)
{


	//---------------------------------------------------Initialisation
	initialisation();

	//---------------------------------------------------Phase Moteur

	//1. Verifier qu'il y a des places disponibles

	// 2.


	//TODO Modifier pour la fin
	char car;
	pid_t voiturier;
	//TODO Modifier la condition pour fin si plus de personne qui écrit sur le canal
	while( read( CanalL, &car, sizeof(char)))
	{
		voiturier = GarerVoiture(PROF_BLAISE_PASCAL);
		
	}
	waitpid(voiturier, NULL, 0);
}

