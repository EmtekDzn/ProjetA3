#include "integration.h"
#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"

/**
 * @fn integrationTest
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

    int i;                                   //Increment de boucle
    float puissance = 0.0;                   //Puissance de chauffage
    float lastTemp = temperature.interieure; //Pour la première boucle, la dernière température est l'actuelle

    for (i = 0; i < nIterations; i++) {
        visualisationT(temperature); //Ecriture de la température dans data.txt
        params.consigne = consigne(params.consigne);
        puissance = regulation(2, &params, params.consigne - temperature.interieure, params.consigne - lastTemp);
            //Régulation de la puissance en fonction de l'erreur actuelle et de la dernière erreur
        visualisationC(puissance);                          //Ecriture de l'état du chauffage dans data.txt
        lastTemp = temperature.interieure;                  //Sauvegarde de la température intérieure pour une prochaine régulation
        temperature = simCalc(puissance, monSimulateur_ps); //Simulation de l'environnement
    }
}
