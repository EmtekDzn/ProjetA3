#include "regulation.h"
/**
 * @fn regulationTest
 * Renvoie la puissance en % ou tout-ou-rien
 * @param regul 1 = tout-ou-rien, 2 = PID
 * @param csgn la température de consigne
 * @param tabT tableau de températures intérieures successives en entrée de la
 * régulation
 * @param nT nombre d’entrées dans le tableau tabT
 * @return la commande
 */
float regulationTest(int regul, float csgn, float *tabT, int nT) {
    float cmd = 100.0;
    params_regul params;
    params.consigne = csgn;
    params.integrale_totale = 0;
    params.mode = regul;
    int i;
    for (i = 1; i < nT; i++) {
        cmd = regulation(&params, csgn - tabT[i], csgn - tabT[i - 1]);
    }
    return cmd;
}

/**
 * @fn regulation
 * Renvoie la puissance en %
 * @param params le pointeur vers la struct params
 * @param err l'erreur actuelle (consigne - Température intérieure)
 * @param last_err l'erreur précédente
 * @return la commande
 */
float regulation(params_regul *params, float err, float last_err) {
    if (params->mode == 1) { // Mode TOR
        if (err > 0) { // Si la température intérieure est inférieure à la consigne
            return 40;
        }
        return 0;
    } else { // Mode PID

        float P = err * KP;
        params->integrale_totale += (err * DELTA_T) - ((err*err)/(2*DELTA_T));
        float I = params->integrale_totale * KI;
        float D = ((err - last_err)/DELTA_T) * KD;

        printf("P : %f\nI : %f\nD : %f\n", P, I, D);
        float PID = P + I + D;
        if (PID > 100)
            PID = 100;
        if (PID < 0)
            PID = 0;
        return PID;
    }
}