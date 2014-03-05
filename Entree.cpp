#include "Entree.h"
#include "Mere.h"



void Entree()
{
	//TODO Modifier pour la fin
	char car;
	pid_t voiturier;
	//TODO Modifier la condition pour fin si plus de personne qui écrit sur le canal
	while( read( canal[0], &car, sizeof(char)))
	{
		voiturier = GarerVoiture(PROF_BLAISE_PASCAL);
		
	}
	waitpid(voiturier, NULL, 0);
}

