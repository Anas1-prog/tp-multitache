/*************************************************************************
                           Clavier  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par kantoine
*************************************************************************/

//---------- Interface de la tâche <Clavier> (fichier Clavier.h) -------
#if ! defined ( CLAVIER_H_ )
#define CLAVIER_H_

//------------------------------------------------------------------------
// Rôle de la tâche <Clavier>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

void Clavier ( int canalS[2],int canalGB[2],int canalPBP[2],int canalABP[2]  );
// Mode d'emploi :
//
// Contrat :
//


void Commande ( char Code, unsigned int valeur );
// Mode d'emploi :
//
// Contrat :
//

#endif // CLAVIER_H_

