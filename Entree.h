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
//	Tâche qui s'occupe de la gestion des entrées de voitures à une barrière
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

//------------------------------------------------------ Include personnel
#include "Util.h"

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
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



