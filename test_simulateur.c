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

void microsleep(__int64 usec)
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}

int main(){
    int i;        // increment de boucle
    float puissance = 70.0; // puissance de chauffage
	float cmd, csgn;
	
    temp_t temperature;
    temperature.exterieure = 14.0;
    temperature.interieure = 16.0;

    struct simParam_s *monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialisee a 0%
    
    float lastTemp = temperature.interieure;
    
    params_regul params;
    params.consigne = 20;
    params.integrale_totale = 0;
    params.mode = 2;

    for (i = 0; i < 10; i++) {
        visualisationT(temperature);
        params.consigne = consigne(params.consigne);
        //puissance = regulation(2, &params, params.consigne - temperature.interieure, params.consigne - lastTemp);
        visualisationC(puissance);
        lastTemp = temperature.interieure;
        temperature = simCalc(puissance, monSimulateur_ps); // simulation de l'environnement
        //microsleep(25e4);
    }
    return EXIT_SUCCESS;
    /** 
	 * Programme USB
	 */

    //FT_HANDLE descr = initUSB();
    FT_HANDLE descr = 0;

    do {
        temperature = releve(descr);
        visualisationT(temperature);
        csgn = consigne(csgn);
        cmd = regulation(3, &params, params.consigne - temperature.interieure, params.consigne - lastTemp);
        visualisationC(cmd);
        commande(descr, cmd);
	} while(1);

	simDestruct(monSimulateur_ps); // destruction de simulateur
	
	//FT_Close(descr);

	return EXIT_SUCCESS;
}
