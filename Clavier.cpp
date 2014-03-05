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


//------------------------------------------------------ Include personnel
#include "Clavier.h"
#include "Menu.h"
#include "Mere.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

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

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier (  )
// Algorithme :
//
{
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
		exit(0);
		break;
	case 'P' :
		switch(valeur)
		{
			//TODO : Ecrire sur le bon canal de communication
			default	:
				char c = 'a';
				write( canal[1], &c, sizeof(char));
				sleep(1);
				break;
		}
		break;
	}
} //----- fin de Commande

