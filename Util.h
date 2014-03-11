//---------- Interface du module <Util> (fichier Util.h) -------------
#ifndef UTIL_H_
#define UTIL_H_

//------------------------------------------------------------------------

//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <time.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "Mere.h"
#include "Outils.h"

//------------------------------------------------------Variable Statiques
//Compteur de matricule entre 0 et 999
static int compteurMatricule;
//------------------------------------------------------------- Constantes
//Places disponibles dans le parking
#define NB_PLACES 8
#define NB_ENTREES 3

extern const int CLEF;
//------------------------------------------------------------------ Types

struct Voiture {
	int matricule;
	TypeUsager usager;
	time_t heureArrivee;

	Voiture ( ) : usager ( AUCUN ) , heureArrivee ( 0 )
	{
		//Vide
	}

	Voiture ( TypeUsager u ) : usager ( u ) , heureArrivee ( 0 )
	{
		matricule = compteurMatricule;
		compteurMatricule++;
		compteurMatricule %= compteurMatricule % 999;
	}

	//-----------------------------------------------Constructeur de copie
	Voiture( const Voiture& voit ) : matricule ( voit.matricule ) , usager ( voit.usager ) , heureArrivee ( voit.heureArrivee )
	{
		//Vide
	}
};



struct RequeteVoiture {
	TypeBarriere barriere;
	Voiture voiture;
	pid_t pid; //Pid du processus Entree
	time_t heureRequete;
	bool actif; //true si il y a une requete, false si il n'y en a pas

	//----------------------------------------------Constructeur par defaut
	RequeteVoiture ( ) : barriere ( AUCUNE ) , voiture ( Voiture ( ) ) , heureRequete ( time ( NULL ) ) , actif ( false )
	{
		pid = 0;
	}

	//---------------------------------------------------------Constructeur
	RequeteVoiture ( TypeBarriere b , Voiture v , pid_t p , time_t t ) : barriere ( b ) , voiture ( v ) , pid ( p ) , heureRequete ( t ) , actif ( true )
	{
		//Vide
	}



};

//Struct de la mémoire patagée
struct EtatParking
{
	int placeLibres;
	int nombreRequetes;
	Voiture place [ NB_PLACES ];
	RequeteVoiture requetes [ NB_ENTREES ];

};



//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Handler( int numSignal, void (*handler) (int) );
// Mode d'emploi :
// Procédure armant le signal numSignal sur la procédure
//	handler
// <clef> : clef de la semaphore
// <semOp> : -1 pour prendre le controle de la semaphore
//			 1 pour redonner le controle
//
// Contrat :
//

void semaphore(int clef, short semOp);
// Mode d'emploi :
//	Procédure qui cherche à récupérer ou à rendre un sémaphore
// Contrat :
//
#endif /* UTIL_H_ */
