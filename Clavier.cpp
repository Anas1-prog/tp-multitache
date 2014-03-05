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
#include <fcntl.h>


//------------------------------------------------------ Include personnel
#include "Clavier.h"
#include "Menu.h"
#include "Mere.h"
#include "Outils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

static int CanalEcritureS;
static int CanalEcritureABP;
static int CanalEcriturePBP;
static int CanalEcritureGB;

//------------------------------------------------------ Fonctions privées
static TypeBarriere getTypeBarriere(int numeroBarriere,TypeUsager usager)
//Mode d'emploi
//Retourne le TypeBarriere correspondant aux parametres entrés au clavier
{
	if (numeroBarriere == 2)
	{
		return ENTREE_GASTON_BERGER;
	}
	else
	{
		if (usager == PROF )
		{
			return PROF_BLAISE_PASCAL;
		}
		else
		{
			return AUTRE_BLAISE_PASCAL;
		}
	}
}

static void fileDeVoiture(TypeBarriere Entree,TypeUsager usager)
//Algo
// Ajoute une nouvelle voiture avec ses proprietes à une entree donnée
{
	//write()
	//Communique avec l'entrée choisie pour lui dire de laisser entrer une nouvelle voiture
}

static void demandeSortie(unsigned int numeroPlace)
//Algorithme :
//
{
	write(CanalEcritureS,&numeroPlace,sizeof(unsigned int));
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier ( int canalLecS, int canalEcrS,int canalLecGB,int canalEcrGB,int canalLecPBP,int canalEcrPBP,int canalLecABP,int canalEcrABP )
// Algorithme :
//
{
	//----------------------------------------------Initialisation


	//----------Ouverture du Canal anonyme Clavier-Sortie
	CanalEcritureS = canalEcrS;
		//Fermeture du coté non utilisé : Lecture
	close(canalLecS);

	//----------Ouverture du canal nommé Clavier-Entree GB
	CanalEcritureGB = canalEcrGB;
		//Fermeture du coté non utilisé : Lecture
	close(canalLecGB);

	//----------Ouverture du canal nommé Clavier-EntreeAutreBlaisePascal(ABP)
	CanalEcritureABP = canalEcrABP;
		//Fermeture du coté non utilisé : Lecture
	close(canalLecABP);

	//----------Ouverture du canal nommé Clavier-EntreeAutreBlaisePascal(PBP)
	CanalEcriturePBP = canalEcrPBP;
		//Fermeture du coté non utilisé : Lecture
	close(canalLecPBP);


	//------------------------------------------------Phase Moteur

	while(true)
	{
		Menu();
	}
} //----- fin de Clavier

void Commande ( char Code, unsigned int valeur )
// Algorithme :
//
{
	switch( Code )
	{
	case 'Q' :
		//Fermeture des canaux de communication avant de quitter l'application
		close(CanalEcritureS);
		close(CanalEcritureGB);
		close(CanalEcritureABP);
		close(CanalEcriturePBP);
		exit(0);
		break;
	case 'P' :
			//Met un nouveau vehicule prioritaire à une barrière d'entrée
		 fileDeVoiture(getTypeBarriere(valeur,PROF),PROF);
		break;
	case 'A' :
			//Met un nouveau véhicule normal à une barrière d'entrée
		fileDeVoiture(getTypeBarriere(valeur,AUTRE),AUTRE);
		break;
	case 'S' :
			//Demande de sortie de la voiture placée à la place valeur
		demandeSortie(valeur);
		break;
	default :
		break;
	}
} //----- fin de Commande

