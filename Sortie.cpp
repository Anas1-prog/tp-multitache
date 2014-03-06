/*************************************************************************
                          Clavier  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par kantoine
*************************************************************************/

//---------- Réalisation de la tâche <Clavier> (fichier Clavier.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//------------------------------------------------------ Include personnel
#include "Sortie.h"
#include "Mere.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
static int CanalLectureS;
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


		//TODO Fonction de comparaison des priorités
//static void comparaisonPriorite()

		//TODO Fonction qui compare les priorités des voitures devant chaque portes et
		//qui signale à l'entrée concerné qu'elle peut faire entrer une nouvelle voiture
//static void choixEntreePrioritaire()

static void initialisation ( )
//Mode d'emploi
//
//Algo
//
{
	SetSignalHandler ( SIGUSR2 , destruction ) ;
	SetSignalHandler ( SIGCHLD , sortieVoiture ) ;

}

static void destruction( int numeroSignal)
//Mode d'emploi
//Appelé lorsqu'on veut détruire la tache sortie
//Algo
//Tue toutes les taches filles en cours
{

}

static void sortieVoiture(int numeroSignal)
//Mode d'emploi
//
//Algo
//
{
	//Maj memoire partagée NbPlace-- et suppression de la PlacedeParking occupée
}
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Sortie ( int canalL,int canalE)
// Algorithme :
//
{
	//------------------------------------------------Initialisation
	CanalLectureS=canalL;
	close(canalE);
	initialisation();

	//------------------------------------------------Phase moteur




} //----- fin de Sortie
