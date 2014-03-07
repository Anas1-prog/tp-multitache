/*************************************************************************
                           Entree  -  description
                             -------------------
    début                : 25 févr. 2014
    copyright            : (C) 2014 par acourjault
    e-mail               : amaury.courjault@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Entree> (fichier Entree.h) -------
#if ! defined ( ENTREE_H )
#define ENTREE_H

//------------------------------------------------------------------------
// Rôle de la tâche <Entree>
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
void initialisation();
// Mode d'emploi :
//
// Contrat :
//


static void destruction(int numSignal);
// Mode d'emploi :
//
// Contrat :
//

void entreeVoiture(int numSignal);
// Mode d'emploi :
//
// Contrat :
//

void Entree(int canal[2], TypeBarriere barriere);
// Mode d'emploi :
//
// Contrat :
//


#endif // ENTREE_H



