#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "ftd2xx.h"
#include "commande.h"
#include "releve.h"

int main(){

	temp_t temp;

	temp.exterieure = 14.0;
	temp.interieure = 15.0;
	struct simParam_s*  monSimulateur_ps = simConstruct(temp); // creation du simulateur, puissance intialis�e � 0%
	int i=0; // increment de boucle
	float puissance = 70.0; // puissance de chauffage
	float csgn = 9;
	float cmd = 20;
	
	/*for(i = 0 ; i < 30 ; i++){
		temp = simCalc(puissance,monSimulateur_ps); // simulation de l'environnement
	}*/


	/**
	 * Programme USB
	 */
	
	//FT_HANDLE descr = initUSB();
	FT_HANDLE descr = 0;

	do {
		temp = releve(descr);
		//visualisationT(temp);
		//csgn = consigne(csgn);
		//cmd = regulation(mode, temp, csgn, param_regul);
		//visualisationC(cmd);
		commande(descr, cmd);
		csgn--;
	} while(csgn > 0);

	simDestruct(monSimulateur_ps); // destruction de simulateur
	
	//FT_Close(descr);
	
	printf("cfini");
	return EXIT_SUCCESS;
}
