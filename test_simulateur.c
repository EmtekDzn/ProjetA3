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


int simulation(){
    int i;        // increment de boucle
    float puissance = 70.0; // puissance de chauffage
	float cmd = 0;
	
    temp_t temperature;
    temperature.exterieure = 14.00;
    temperature.interieure = 14.00;

    struct simParam_s *monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialisee a 0%
    
    float lastTemp = temperature.interieure;
    
    params_regul params;
    params.consigne = 20;
    params.integrale_totale = 0;
    params.mode = 2;
    /**
     * Programme simulé
     */
    for (i = 0; i < 2000; i++) {
        visualisationT(temperature);
        params.consigne = consigne(params.consigne);
        puissance = regulation(2, &params, params.consigne - temperature.interieure, params.consigne - lastTemp);
        visualisationC(puissance);
        lastTemp = temperature.interieure;
        temperature = simCalc(puissance, monSimulateur_ps); // simulation de l'environnement
        usleep(5e4);
    }

	simDestruct(monSimulateur_ps); // destruction de simulateur
	
	return EXIT_SUCCESS;
}
