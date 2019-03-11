#include "regulation.h"
/**
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
    params.somme_erreurs = 0;
    params.mode = regul;
    int i;
    for (i = 1; i < nT; i++) {
        cmd = regulation(&params, csgn - tabT[i], csgn - tabT[i - 1]);
    }
    return cmd;
}

/**
 * Renvoie la puissance en %
 * @param params le pointeur vers la struct params
 * @param temp_int la température intérieure
 * @param last_temp_int la température intérieure précédente
 * @return la commande
 */
float regulation(params_regul *params, float err, float last_err) {
    if (params->mode == 1) {
        if (err > 0) {
            return 40;
        }
        return 0;
    } else {
        params->somme_erreurs += err;
        float P = err * KP;
        float I = P + params->somme_erreurs * KI;
        float D = P + (err - last_err) * KD;
        printf("P : %.2f\nI : %.2f\nD : %.2f\n", P, I, D);
        float PID = P + I + D;
        if (PID > 100)
            PID = 100;
        return PID;
    }
}