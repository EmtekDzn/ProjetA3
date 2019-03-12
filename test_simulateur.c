#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "ftd2xx.h"
#include "commande.h"
#include "releve.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"
#include "consigne.h"

int main(){
    params_regul params;
    params.consigne = 20;
    params.somme_erreurs = 0;
    params.mode = 2;

	temp_t temperature;
    temperature.exterieure = 14.0;
    temperature.interieure = 16.0;

    struct simParam_s *monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%

    int i;        // increment de boucle
    float puissance = 70.0; // puissance de chauffage
	float cmd = 20;
	float csgn;

	float lastTemp = temperature.interieure;
    for (i = 0; i < 5; i++) {
        visualisationT(temperature);
        params.consigne = consigne(params.consigne);
        printf("Changement puissance, Tint : %.1f,    LastTint : %.1f\n", temperature.interieure, lastTemp);
        puissance = regulation(&params, params.consigne - temperature.interieure, params.consigne - lastTemp);
        visualisationC(puissance);
        lastTemp = temperature.interieure;
        temperature = simCalc(puissance, monSimulateur_ps); // simulation de l'environnement
		usleep(5e4);
        
    }

	/**
	 * Programme USB
	 */
	
	//FT_HANDLE descr = initUSB();
	FT_HANDLE descr = 0;

	do {
		temperature = releve(descr);
		visualisationT(temperature);
		csgn = consigne(csgn);
		cmd = regulation(mode, temp, csgn, param_regul);
		visualisationC(cmd);
		commande(descr, cmd);
	} while(1);

	simDestruct(monSimulateur_ps); // destruction de simulateur
	
	//FT_Close(descr);
	
	printf("cfini");
	return EXIT_SUCCESS;
}
