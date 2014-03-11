
/*************************************************************************
                          Util  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par Antoine Kevin
*************************************************************************/

//---------- Réalisation du module <Util> (fichier Util.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Util.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Handler ( int numSignal , void ( *handler ) ( int ) )
// Algorithme :
//
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset ( &action.sa_mask );
	action.sa_flags = 0;
	sigaction ( numSignal , &action , NULL );
} // Fin de Handler


void semaphore ( int clef , short semOp )
// Algorithme :
//
{
	int semId = semget ( CLEF , 1 , IPC_EXCL );
	sembuf listeOp = sembuf( );
	listeOp.sem_num = 0;
	listeOp.sem_op = semOp;
	listeOp.sem_flg = IPC_NOWAIT;//Pour appel systeme non blocant (IPC_NOWAIT)
	int testSem = -1;
	while ( testSem == -1 )
	{
		testSem = semop ( semId , &listeOp , 1 );
	}
}

