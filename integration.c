#include "integration.h"
#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"

/**
 * Réalise l'intégration des fonctions
 * @param regul 1 = tout-ou-rien, 2 = PID
 * @param tInit les températures initiales
 * @param nInterations le nombre d'itérations du programme
 */
void integrationTest(int regul, temp_t tInit, int nIterations) {
    params_regul params;
    params.consigne = 20;
    params.integrale_totale = 0;
    params.mode = regul;

    temp_t temperature = tInit;

    struct simParam_s *monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%

    int i;                 // increment de boucle
    float puissance = 0.0; // puissance de chauffage
    float lastTemp = temperature.interieure;
    for (i = 0; i < nIterations; i++) {
        visualisationT(temperature);
        params.consigne = consigne(params.consigne);
        puissance = regulation(2, &params, params.consigne - temperature.interieure, params.consigne - lastTemp);
        visualisationC(puissance);
        lastTemp = temperature.interieure;
        temperature = simCalc(puissance, monSimulateur_ps); // simulation de l'environnement
    }
}
