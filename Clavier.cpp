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

static int canalEcritureS;
static int canalEcritureABP;
static int canalEcriturePBP;
static int canalEcritureGB;
static int canalCommun;

//------------------------------------------------------ Fonctions privées
static TypeBarriere getTypeBarriere(int numeroBarriere,TypeUsager usager)
//Mode d'emploi
//Retourne le TypeBarriere correspondant aux parametres entrés au clavier
//Met une nouvelle valeur au canal commun qui prend la valeur du canal concerné
{
	if (numeroBarriere == 2)
	{
		canalCommun = canalEcritureGB;
		return ENTREE_GASTON_BERGER;
	}
	else
	{
		if (usager == PROF )
		{
			canalCommun = canalEcriturePBP;
			return PROF_BLAISE_PASCAL;
		}
		else
		{
			canalCommun = canalEcritureABP;
			return AUTRE_BLAISE_PASCAL;
		}
	}
}

static void fileDeVoiture(TypeBarriere entree,TypeUsager usager)
//Algo
// Ajoute une nouvelle voiture avec ses proprietes à une entree donnée
{
	char c='N';
	DessinerVoitureBarriere(entree, usager );
	write( canalCommun, &c, sizeof(c) );
	//write()
	//Communique avec l'entrée choisie pour lui dire de laisser entrer une nouvelle voiture
}

static void demandeSortie(unsigned int numeroPlace)
//Algorithme :
//
{
	write(canalEcritureS,&numeroPlace,sizeof(unsigned int));
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier ( int canalS[2],int canalGB[2],int canalPBP[2],int canalABP[2] )
// Algorithme :
//
{
	//----------------------------------------------Initialisation




	//----------Ouverture du canal nommé Clavier-Entree GB
	canalEcritureS = canalS[1];
		//Fermeture du coté non utilisé : Lecture Clavier Sortie
	close(canalS[0]);

	//----------Ouverture du canal nommé Clavier-Entree GB
	canalEcritureGB = canalGB[1];
	//Fermeture du coté non utilisé : Lecture Clavier-Entree GB
	close(canalGB[0]);

	//----------Ouverture du canal nommé Clavier-EntreeAutreBlaisePascal(ABP)
	canalEcritureABP = canalABP[1];
	//Fermeture du coté non utilisé : Lecture
	close(canalABP[0]);

	//----------Ouverture du canal nommé Clavier-EntreeAutreBlaisePascal(PBP)
	canalEcriturePBP = canalPBP[1];
	//Fermeture du coté non utilisé : Lecture
	close(canalPBP[0]);


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
		close(canalEcritureS);
		close(canalEcritureGB);
		close(canalEcritureABP);
		close(canalEcriturePBP);
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

