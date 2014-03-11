
/*************************************************************************
                          Clavier  -  description
                             -------------------
    début                : 18 févr. 2014
    copyright            : (C) 2014 par Amaury
*************************************************************************/

//---------- Réalisation de la tâche <Entree> (fichier Entree.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sstream>

//------------------------------------------------------ Include personnel
#include "Entree.h"
#include "Mere.h"
#include "Outils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
//Temps pendant lequel il faut que la tache dorme après avoir laissé entrer une voiture
#define ENTREE_DELAIS 1
//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int canalLectureE;
static int autorisationPassage;
static map < pid_t,Voiture > voiturierEntree;
extern const key_t CLEF;
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

static void requeteEntree ( TypeBarriere barriere , Voiture voiture )
// Mode d'emploi :Crée une requete de demande d'entrée lorsqu'aucune place n'est occupée
//
// Contrat : Gestion de l'affichage à l'écran dans la fonction
//
// Algorithme :
//
{
	time_t heureArr = time ( NULL );
	RequeteVoiture requete = RequeteVoiture ( barriere , voiture , getpid( ) , heureArr );
	//Prise du Mutex
		semaphore( CLEF , -1 );

	//Acces memoire partagée
	int memoirePartagee = shmget ( CLEF , sizeof( EtatParking ), IPC_EXCL );
	EtatParking * etat = ( EtatParking * ) shmat ( memoirePartagee , NULL , 0 );
	etat->requetes[ barriere - 1 ] = requete;
	etat->nombreRequetes++;
	//Libere le Mutex
	semaphore ( CLEF , 1 );
	//Libere la memoire
	shmdt ( etat );

	AfficherRequete ( barriere , voiture.usager , heureArr );
}

static void entreeVoiture ( int numSignal )
// Mode d'emploi :
//
// Contrat : Decrementation se fait avant car on ne peut pas attendre
//			 que la voiture soit garée pour signaler que la place est prise
//
// Algorithme :
//
{
	int crdu;
	pid_t pid;

	//Verifie la fin d'un fils, WNOHANG : non bloquant
	while ( ( pid = waitpid ( -1 , &crdu , WNOHANG ) ) > 0 )
	{
		if ( WIFEXITED ( crdu ) )
		{
			int numPlace = WEXITSTATUS ( crdu );
			Voiture voiture = voiturierEntree[ pid ];
			voiture.heureArrivee = time ( NULL );
			//Suppression de la liste des voituriers qui travaillent
			voiturierEntree.erase ( pid );
			
			//Acces memoire partagée
			int memoirePartagee = shmget ( CLEF , sizeof( EtatParking ) , IPC_EXCL );
			EtatParking * etat = ( EtatParking * ) shmat ( memoirePartagee , NULL , 0 );

			//Prise du Mutex
			semaphore ( CLEF , -1 );
			//Ajout de la voiture qui vient d'entrer dans la memoire
			etat->place[ numPlace - 1 ] = voiture;
			//Libere le Mutex
			semaphore ( CLEF , 1 );

			//Libere la memoire
			shmdt ( etat );


			//Afficher la voiture sur la memoire terminal
			AfficherPlace ( numPlace , voiture.usager , voiture.matricule , voiture.heureArrivee );

		}
	}
} //----- fin de entreeVoiture

static void initialisationEntree ( )
//Mode d'emploi
//	Masque le signal SIGUSR1
//	Arme le signal SIGUSR2 sur destructionEntree
// 	et SIGCHLD sur entreeVoiture
//Algo
//
{
	Handler ( SIGUSR1, SIG_IGN );
	Handler ( SIGUSR2 , destructionEntree ) ;
	Handler ( SIGCHLD , entreeVoiture ) ;
}

static void destructionEntree ( int numSignal )
//Mode d'emploi
//	Declenché par la reception du signal SIGUSR2
// 	Libération des ressources et des tâches allouées par cette tâche
//Algorithme
//
{
	//Masquage du signal SIGCHLD
	Handler( SIGCHLD , SIG_IGN );

	for ( map< pid_t, Voiture > :: iterator iter = voiturierEntree.begin( ) ;
			iter != voiturierEntree.end( ) ; ++iter )
	{

		kill ( iter->first , SIGUSR2 );
		waitpid ( iter->first , NULL , 0 );
	}
	exit ( 0 );
}

static void passageVoiture ( int numSignal )
// Mode d'emploi :
//	Déclenché à la réception d'un signal SIGUSR1
// Contrat :
//
// Algorithme :
//
{
	autorisationPassage = true;
}

static int verificationPlacesLibres ( )
//Mode d'emploi
//	Attachement mémoire pour renvoyer le nombre de places disponibles
{
	//Attachement memoire partagée
	int memoirePartagee = shmget ( CLEF , sizeof( EtatParking ) , IPC_EXCL );
	EtatParking * etat = ( EtatParking * ) shmat ( memoirePartagee , NULL , 0 );
	//Prise du Mutex
	semaphore ( CLEF , -1 );
	int placeLibre = etat->placeLibres;
	//Libere le Mutex
		semaphore ( CLEF , 1 );
	//Detache de la memoire
	shmdt ( etat );
	return placeLibre;
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Entree ( int canal[ 2 ] , TypeBarriere barriere )
// Algorithme :
//	
{
	int lecture;
	RequeteVoiture message;
	canalLectureE = canal[ 0 ];
	close ( canal[ 1 ] );

	//---------------------------------------------------Initialisation
	initialisationEntree ( );

	//---------------------------------------------------Phase Moteur

	for( ; ; )
	{
		lecture = read ( canalLectureE , &message , sizeof ( RequeteVoiture ) );
		
		if ( lecture > 0 )
		{
			//Verification si il y a des places de libres dans le parking :
			if ( !verificationPlacesLibres ( ) > 0 )
			{
				//Place une requete pour entrer dans la mémoire
				requeteEntree ( message.barriere , message.voiture );
				autorisationPassage = false;
				//Attente de l'envoi d'un signal par la sortie
				Handler ( SIGUSR1 , passageVoiture );
				while( !autorisationPassage )
				{
					pause ( );
				}
				Handler ( SIGUSR1 , SIG_IGN );//Masquage du signal
			}

			//Acces memoire partagée
			int memoirePartagee = shmget ( CLEF , sizeof ( EtatParking ) , IPC_EXCL );
			EtatParking * etat = ( EtatParking * ) shmat ( memoirePartagee , NULL , 0 );

			//Prise du Mutex
			semaphore ( CLEF , -1 );
			//Ajout de la voiture qui vient d'entrer dans la memoire et decrementation nb place
			etat->placeLibres--;
			//Libere le Mutex
			semaphore ( CLEF , 1 );

			//Libere la memoire
			shmdt ( etat );

			pid_t voiturier = GarerVoiture ( barriere );

			voiturierEntree[ voiturier ] = message.voiture;
			sleep ( ENTREE_DELAIS );
		}
	}
}
