/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par kantoine
*************************************************************************/

//---------- Interface de la tâche <Mere> (fichier Mere.h) -------
#if ! defined ( MERE_H_ )
#define MERE_H_

//------------------------------------------------------------------------
// Rôle de la tâche <Mere>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
static int CanalS[2];
static int CanalGB[2];
static int CanalPBP[2];
static int CanalABP[2];
//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//
void finHeure (int noSignal);
// Mode d'emploi :
//
// Contrat :
//

void SetSignalHandler(int signalNumber, void (*handler) (int) );
// Mode d'emploi :
//Prend en parametre le signal et lui attribue une fonction que la tache executera
//à la reception de ce signal
// Contrat :
//

#endif // MERE_H_
