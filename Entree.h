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
static void initialisation();
// Mode d'emploi :
//
// Contrat :
//


static void destruction();
// Mode d'emploi :
//
// Contrat :
//

static void entreeVoiture();
// Mode d'emploi :
//
// Contrat :
//

void Entree(int canalL,int canalE);
// Mode d'emploi :
//
// Contrat :
//


#endif // ENTREE_H



