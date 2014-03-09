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
extern key_t const CLEF;
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


static bool comparaisonPriorite(RequeteVoiture req1, RequeteVoiture req2)
// Mode d'emploi :
// Retourne true si req1 est prioritaire
//Retourne false si req2 est prioritaire
// Contrat :
//
// Algorithme :
//
{
	//Vérifie d'abord la pertinance de la requete stocké dans le tableau
	//La fonction va comparer toutes les requetes de la mémoire partagée,
	//meme celle qui sont vides.
	if (!req1.actif)
	{
		return false;
	}
	if (!req2.actif)
	{
		return true;
	}

	//Cas normal : comparaison des priorités.
	if (req1.voiture.usager==PROF)
	{
		if(req2.voiture.usager==AUTRE)
		{
			return true;
		}
		else
		{
			if (req1.heureRequete>=req2.heureRequete)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	}
	else
	{
		if (req2.voiture.usager==PROF)
		{
			return false;
		}
		else
		{
			if (req1.heureRequete>=req2.heureRequete)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}


static void choixEntreePrioritaire()
//Mode d'emploi
//Fonction appelée lorsqu'une place vient de se libérer
//La sortie doit choisir quelle entrée est la plus prioritaire parmis les requetes.
//Algo
//
//Contrat : Gestion de l'affichage intégré
{

	//Attachement memoire partagée
	int memoirePartagee = shmget ( CLEF , sizeof(EtatParking), IPC_EXCL);
	EtatParking * etat = (EtatParking *)shmat(memoirePartagee, NULL, 0);
	//Prise du Mutex
	semaphore(CLEF,-1);
	RequeteVoiture requete[NB_ENTREES] = etat->requetes;
	int nombreRequetes = etat->nombreRequetes;
	//Libere le Mutex
	semaphore(CLEF,1);

	if(nombreRequetes>0)
	{
		//Recupere la requete la plus prioritaire
		int prio=0;
		for (int i =1; i<NB_ENTREES;i++)
		{
			if (comparaisonPriorite(requete[i],requete[prio]))
			{
				prio=i;
			}
		}

		//envoie SIGUSR1 à l'entrée concernée
		kill(requete[prio].pid,SIGUSR1);
		//Prise du Mutex
		semaphore(CLEF,-1);
		etat->nombreRequetes--;
		etat->requetes[prio].actif=false;//desactive la requête.
		//Libere le Mutex
		semaphore(CLEF,1);

		//Detache de la mémoire
		shmdt(etat);



	}

}

void initialisationSortie ( )
//Mode d'emploi
//
//Algo
//
{
	Handler ( SIGUSR2 , destructionSortie ) ;
	Handler ( SIGCHLD , sortieVoiture ) ;

}

void destructionSortie( int signal)
//Mode d'emploi
//Appelé lorsqu'on veut détruire la tache sortie
//Algo
{
	if(signal == SIGINT)
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

	//Verifie la fin d'un fils, WNOHANG : non bloquant car le fils est déjà mort (en theorie)
	while ( (pid = waitpid(-1,&crdu,WNOHANG) ) > 0 )
	{
		if (WIFEXITED ( crdu ))
		{
			int numPlace = WEXITSTATUS ( crdu );
			//Suppression de la liste des voituriers
			voiturierSortie.erase(numPlace-1);

			//Acces memoire partagée
			int memoirePartagee = shmget ( CLEF , sizeof(EtatParking), IPC_EXCL);
			EtatParking * etat = (EtatParking *)shmat(memoirePartagee, NULL, 0);

			//Prise du Mutex
			semaphore(CLEF,-1);
			//Retrait de la voiture qui vient de sortir dans la memoire
			//et decrementation nb place
			etat->placeLibres++;
			Voiture voiture = etat->place[numPlace];

			//Libere le Mutex
			semaphore(CLEF,1);

			//Libere la memoire
			shmdt(etat);

			AfficherSortie(voiture.usager,voiture.matricule,voiture.heureArrivee,time(NULL));
			//Effacement de la zone à l'écran
			Effacer( ( TypeZone )( ETAT_P1 + ( numPlace - 1 ) ) );

			choixEntreePrioritaire();
		}
	}
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
			//Vérifie si la tache n'est pas déjà créee
			if (voiturierSortie.find(numPlace) == voiturierSortie.end())
			{
				pid_t voiturierpid = SortirVoiture(numPlace);
				if (voiturierpid != -1)
				{
					voiturierSortie[numPlace] = voiturierpid;
				}
			}
		}
	}



} //----- fin de Sortie
