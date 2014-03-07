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


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
static int canalLectureS;
static map<int, pid_t> voiturierSortie;
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

void initialisationSortie ( )
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

	for ( map<int, pid_t>::iterator it = voiturierSortie.begin();
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

	int crdu;
	pid_t pid;

	//Verifie la fin d'un fils, WNOHANG : non bloquant
	while ( (pid = waitpid(-1,&crdu,WNOHANG) ) > 0 )
	{
		if (WIFEXITED ( crdu ))
		{
			int numPlace = WEXITSTATUS ( crdu );
			int numPlace = voiturierSortie.find(pid);
			//Suppression de la liste des voituriers qui travaillent
			voiturierSortie.erase(numPlace-1);


	//Prise du Mutex
	semaphore(CLEF,-1);
	//Acces memoire partagée
	int memoirePartagee = shmget ( CLEF , sizeof(EtatParking), IPC_EXCL);
	EtatParking * etat = (EtatParking *)shmat(memoirePartagee, NULL, 0);

	//Retrait de la voiture qui vient de sortir dans la memoire et decrementation nb place

	etat->placeLibres++;

	//Libere la memoire
	shmdt(etat);
	//Libere le Mutex
	semaphore(CLEF,1);


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
	initialisationSortie();

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
