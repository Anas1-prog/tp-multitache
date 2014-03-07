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
#include "Outils.h"
//------------------------------------------------------Variable Statiques
//Compteur de matricule entre 0 et 999
static int compteurMatricule;

//------------------------------------------------------------- Constantes
//Places disponibles dans le parking
#define NB_PLACES 8
#define NB_ENTREES 3

//------------------------------------------------------------------ Types

struct Voiture {
	int matricule;
	TypeUsager usager;
	time_t heureArrivee;

	Voiture(TypeUsager u): usager(u),heureArrivee(0)
	{
		matricule = compteurMatricule;
		compteurMatricule++;
		compteurMatricule%=compteurMatricule%999;
	}

	//-----------------------------------------------Constructeur de copie
	Voiture(const Voiture& voit):matricule(voit.matricule),usager(voit.usager),heureArrivee(voit.heureArrivee)
	{
		//Vide
	}
};



struct RequeteVoiture {
	TypeBarriere barriere;
	Voiture voiture;

//	//----------------------------------------------Constructeur par defaut
//	RequeteVoiture():barriere(AUCUNE),heure(0),voiture(Voiture())
//	{
//		//Vide
//	}

	//---------------------------------------------------------Constructeur
	RequeteVoiture(TypeBarriere b, Voiture v):barriere(b),voiture(v)
	{
		//Vide
	}



};

//Struct de la mémoire patagée
struct EtatParking
{
	int placeLibres;
	Voiture place[NB_PLACES];
	RequeteVoiture requetes[NB_ENTREES];
};

#endif /* UTIL_H_ */

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

static void Handler( int numSignal, void (*handler) (int) );
static void semaphore(int clef, short semOp);
