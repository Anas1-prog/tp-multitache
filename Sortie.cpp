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
#include <iostream>
#include <map>
//------------------------------------------------------ Include personnel
#include "Sortie.h"
#include "Mere.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
static int canalLectureS;
static map<pid_t, Voiture> voiturierSortie;
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
	Handler ( SIGUSR2 , destructionSortie ) ;
	Handler ( SIGCHLD , sortieVoiture ) ;

}

void destructionSortie( int numeroSignal)
//Mode d'emploi
//Appelé lorsqu'on veut détruire la tache sortie
//Algo
{
	//Masquage du signal SIGCHLD
	Handler(SIGCHLD, SIG_IGN);

	for ( map<pid_t, Voiture>::iterator it = voiturierSortie.begin();
			it != voiturierSortie.end(); ++it )
	{
		kill ( it->first, SIGUSR2 );
		waitpid( it->first, NULL, 0 );
	}
	exit(0);
}

void sortieVoiture(int numeroSignal)
//Mode d'emploi
//
//Algo
//
{
	//Maj memoire partagée NbPlace-- et suppression de la PlacedeParking occupée
}
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Sortie ( int canal[2])
// Algorithme :
//
{
	//------------------------------------------------Initialisation
	canalLectureS=canal[0];
	int lecture;
	int numPlace;
	close(canal[1]);//Fermeture du canal de lecture
	initialisation();

	//------------------------------------------------Phase moteur
	for (;;)
	{
		lecture = read(canalLectureS,&numPlace, sizeof(int));

		if(lecture>0)
		{
			if (voiturierSortie.find(numPlace) == voiturierSortie.end())
			{
				pid_t voiturierpid = SortirVoiture(numPlace);
				if (voiturierpid !=-1)
				{
					voiturierSortie[numPlace] = voiturierpid;
				}
			}
		}
	}



} //----- fin de Sortie
