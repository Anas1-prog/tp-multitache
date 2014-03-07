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
#include <unistd.h>
#include "Outils.h"
#include <sys/types.h>
#include <sys/wait.h>

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
void destruction(int numeroSignal);
void sortieVoiture(int numeroSignal);


#endif /* SORTIE_H_ */
