/*************************************************************************
                           Sortie  -  description
                             -------------------
    début                : 25 févr. 2014
    copyright            : (C) 2014 par acourjault
    e-mail               : amaury.courjault@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Sortie> (fichier Sortie.h) -------
#if ! defined ( SORTIE_H )
#define SORTIE_H

//------------------------------------------------------------------------
// Rôle de la tâche <Sortie>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Outils.h"
#include "Mere.h"
#include "Util.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

void Sortie ( int canal[2]);
void destructionSortie(int numeroSignal);
void sortieVoiture(int numeroSignal);
void initialisationSortie();


#endif /* SORTIE_H_ */
