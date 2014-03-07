
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

	for ( map<int, pid_t>::iterator iter = voiturierEntree.begin();iter != voiturierEntree.end(); ++iter )
	{
		kill ( iter->first, SIGUSR2 );
		waitpid( iter->first, NULL, 0 );
	}
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
			sleep(ENTREE_DELAIS);
		}
		else if (lecture == 0)
		{
			close(canalLectureE);
			exit(0);
		}
	}
}

