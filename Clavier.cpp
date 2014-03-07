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
//#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

//------------------------------------------------------ Include personnel
#include "Clavier.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

static int canalS[2];
static int canalABP[2];
static int canalPBP[2];
static int canalGB[2];
static int canalCommun;
extern const int CLEF;

//------------------------------------------------------ Fonctions privées
static TypeBarriere getTypeBarriere(int numeroBarriere,TypeUsager usager)
//Mode d'emploi
//Retourne le TypeBarriere correspondant aux parametres entrés au clavier
//Met une nouvelle valeur au canal commun qui prend la valeur du canal concerné
{
	if (numeroBarriere == 2)
	{
		canalCommun = canalGB[1];
		return ENTREE_GASTON_BERGER;
	}
	else
	{
		if (usager == PROF )
		{
			canalCommun = canalPBP[1];
			return PROF_BLAISE_PASCAL;
		}
		else
		{
			canalCommun = canalABP[1];
			return AUTRE_BLAISE_PASCAL;
		}
	}
}

static void fileDeVoiture(TypeBarriere entree,TypeUsager usager)
//Algo
// Ajoute une nouvelle voiture avec ses proprietes à une entree donnée
{
	Voiture voiture = Voiture(usager);
	RequeteVoiture message = RequeteVoiture(entree,voiture);
	DessinerVoitureBarriere(entree, usager );
	write( canalCommun, &message, sizeof(message) );
	//write()
	//Communique avec l'entrée choisie pour lui dire de laisser entrer une nouvelle voiture
}

static void demandeSortie(unsigned int numeroPlace)
//Algorithme :
//
{
	write(canalS[1],&numeroPlace,sizeof(unsigned int));
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier ( int canals[2],int canalgb[2],int canalpbp[2],int canalabp[2] )
// Algorithme :
//
{
	//----------------------------------------------Initialisation

	//----------Ouverture des canaux nommé Clavier-Entree et Sortie
	canalS[1] = canals[1];
	canalGB[1] = canalgb[1];
	canalABP[1] = canalabp[1];
	canalPBP[1] = canalpbp[1];

	//Fermeture des cotés non utilisés
	close(canalS[0]);
	close(canalGB[0]);
	close(canalABP[0]);
	close(canalPBP[0]);

	//------------------------------------------------Phase Moteur
	while(true)
	{
		Menu();
	}
} //----- fin de Clavier

void Commande ( char code, unsigned int valeur )
// Algorithme :
//
{
	switch( code )
	{
	case 'Q' :
		//Fermeture des canaux de communication avant de quitter l'application
			close(canalS[1]);
			close(canalGB[1]);
			close(canalABP[1]);
			close(canalPBP[1]);
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

