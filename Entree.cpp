
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
static int canalLectureE;
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
	SetSignalHandler ( SIGUSR2 , destruction ) ;
	SetSignalHandler ( SIGCHLD , entreeVoiture ) ;
}

static void destruction (int numSignal)
//Mode d'emploi
//Declenche par la reception du signal SIGUSR2
//Algorithme
//
{
	//Masquage du signal SIGCHLD
	SetSignalHandler(SIGCHLD, SIG_IGN);

	//Kill tous les voituriers en cours


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

