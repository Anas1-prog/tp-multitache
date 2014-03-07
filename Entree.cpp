
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


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
//Temps pendant lequel il faut que la tache dorme après avoir laissé entrer une voiture
#define ENTREE_DELAIS 1
//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int canalLectureE;
static int autorisationPassage;
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

void initialisationEntree ( )
//Mode d'emploi
//
//Algo
//
{
	Handler ( SIGUSR2 , destructionEntree ) ;
	Handler ( SIGCHLD , entreeVoiture ) ;
}

void destructionEntree (int numSignal)
//Mode d'emploi
//Declenche par la reception du signal SIGUSR2
//Algorithme
//
{
	//Masquage du signal SIGCHLD
	Handler(SIGCHLD, SIG_IGN);

	for ( map<unsigned int, pid_t>::iterator iter = voiturierEntree.begin();iter != voiturierEntree.end(); ++iter )
	{
		kill ( iter->first, SIGUSR2 );
		waitpid( iter->first, NULL, 0 );
	}
	exit(0);
}

void passageVoiture(int numSignal)
{
	autorisationPassage = true;
}

int verificationPlacesLibres()
{

	//Prise du Mutex
	semaphore(CLEF,-1);

	//Acces memoire partagée
	int memoirePartagee = shmget ( CLEF , sizeof(EtatParking), IPC_EXCL);
	EtatParking * etat = (EtatParking *)shmat(memoirePartagee, NULL, 0);
	return etat->placeLibres;
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques


void Entree(int canal[2], TypeBarriere barriere)
{

	int lecture=0;
	RequeteVoiture message;
	canalLectureE=canal[0];
	close(canal[1]);


	//---------------------------------------------------Initialisation
	initialisationEntree();

	//---------------------------------------------------Phase Moteur


	for(;;)
	{
		lecture = read( canalLectureE, &message, sizeof( char ) );
		
		if ( lecture > 0 )
		{

			//Verification si il y a des places de libres dans le parking :
			if (verificationPlacesLibres()<0)
			{
				//Attente de l'envoi d'un signal par la sortie
				Handler(SIGUSR1, passageVoiture );
				autorisationPassage = false;
			}


		GarerVoiture(barriere);
		sleep(ENTREE_DELAIS);


		}
		else if (lecture == 0)
		{
			close(canalLectureE);
			exit(0);
		}
	}
}

