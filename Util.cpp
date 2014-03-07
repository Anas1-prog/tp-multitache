
/*************************************************************************
                          Clavier  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par Antoine Kevin
*************************************************************************/

//---------- Réalisation de la tâche <Util> (fichier Util.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Util.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
extern const int CLEF;
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
void Handler ( int numSignal, void (*handler) (int) )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset ( &action.sa_mask );
	action.sa_flags = 0;
	sigaction ( numSignal, &action, NULL );
} // Fin de Handler


void semaphore(int clef,short semOp)
// Mode d'emploi :
// <clef> : clef de la semaphore
//<semOp> : -1 pour prendre le controle de la semaphore
//			 1 pour redonner le controle
// Contrat :
//
// Algorithme :
//
{
	int semId = semget ( CLEF , 1 , IPC_EXCL );
	sembuf listeOp =sembuf();
	listeOp.sem_num=0;
	listeOp.sem_op=semOp;
	listeOp.sem_flg=IPC_NOWAIT;//Pour appel systeme non blocant (IPC_NOWAIT)
	int testSem=-1;
	while(testSem==-1)
	{
		testSem = semop ( semId, &listeOp, 1);
	}
}

