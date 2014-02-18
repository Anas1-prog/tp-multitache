#include "Outils.h"
#include <unistd.h>


int main (void)
{
	InitialiserApplication(XTERM);
	sleep(10);	//Attention	//Point triple
	TerminerApplication(true);
	return 0;
}
