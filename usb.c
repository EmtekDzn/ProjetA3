#include <stdio.h>
#include <stdlib.h>
#include "ftd2xx.h"
#include "commande.h"
#include "releve.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"
#include "consigne.h"


int main(){
    float puissance = 70.0; // puissance de chauffage
	float cmd = 0;
	
    temp_t temperature;
    temperature.exterieure = 24.64;
    temperature.interieure = 14.00;
    
    float lastTemp = temperature.interieure;
    
    params_regul params;
    params.consigne = 20;
    params.integrale_totale = 0;
    params.mode = 2;

    do {
        temperature = releve(); // Recupere les temperatures sur la carte
        visualisationT(temperature); // Les ecrit dans data.txt
        params.consigne = consigne(params.consigne); // Recupere la valeur de la consigne
        cmd = regulation(3, &params, params.consigne - temperature.interieure, params.consigne - lastTemp); // Calcule la commande de chauffage (puissance)
        visualisationC(cmd); // Ecrit cette valeur dans data.txt
        lastTemp = temperature.interieure; // Stocke temporairement des temperatures
        commande(cmd); // Envoie la commande sur la carte
	} while(params.consigne > 5); // Tant que la consigne est > 5
	
	return EXIT_SUCCESS;
}
