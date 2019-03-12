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
    int i;        // increment de boucle
    float puissance = 70.0; // puissance de chauffage
	float cmd, csgn;
    float newConsigne;
	
    temp_t temperature;
    temperature.exterieure = 14.0;
    temperature.interieure = 16.0;

    float lastTemp = temperature.interieure;
    
    params_regul params;
    params.consigne = 20;
    params.integrale_totale = 0;
    params.mode = 2;

    struct simParam_s *monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%

    for (i = 0; i < 1000; i++) {
        visualisationT(temperature);
        newConsigne = consigne(params.consigne);
        
        if (params.consigne != newConsigne) {
            params.integrale_totale = 0;
        }
        
        params.consigne = newConsigne;
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
		cmd = regulation(&params, params.consigne - temperature.interieure, params.consigne - lastTemp);
		visualisationC(cmd);
		commande(descr, cmd);
	} while(1);

	simDestruct(monSimulateur_ps); // destruction de simulateur
	
	//FT_Close(descr);

	return EXIT_SUCCESS;
}
