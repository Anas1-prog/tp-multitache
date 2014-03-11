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
//	Tâche qui s'occupe de faire sortir des voitures du Parking
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

void Sortie ( int canal [ 2 ] );
// Mode d'emploi :
//	Procédure de gestion d'une porte de sortie du parking.
// <canal[2]> canal de communication entre la tache Clavier et la tâche Sortie
// Contrat :
//
#endif /* SORTIE_H_ */
