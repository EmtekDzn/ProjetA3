#include "regulation.h"
/**
 * @fn regulationTest
 * Renvoie la puissance en % ou tout-ou-rien (pour les tests unitaires)
 * @param regul le mode de régulation 1 = tout-ou-rien, 2 = PID
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
        cmd = regulation(1, &params, csgn - tabT[i], csgn - tabT[i - 1]);
    }
    return cmd;
}

/**
 * @fn regulation
 * Renvoie la puissance en %
 * @param mode_PID (1=tests unitaires, 2=simu, 3=USB)
 * @param params le pointeur vers la struct params
 * @param err l'erreur actuelle (consigne - Température intérieure)
 * @param last_err l'erreur précédente (consigne - Température intérieure précédente)
 * @return la commande
 */
float regulation(int mode_PID, params_regul *params, float err, float last_err) {
    if (params->mode == 1) { // Mode TOR
        if (err > 0) {       // Si la température intérieure est inférieure à la consigne
            return 40;
        }
        return 0;
    } else { // Mode PID
        float ki, kd, kp;
        switch (mode_PID) {
        case 1: //Mode tests unitaires
            ki = KI_UNIT;
            kd = KD_UNIT;
            kp = KP_UNIT;
            break;
        case 2: //Mode simulation
            ki = KI_SIMU;
            kd = KD_SIMU;
            kp = KP_SIMU;
            break;
        case 3: //Mode USB
            ki = KI_USB;
            kd = KD_USB;
            kp = KP_USB;
            break;
        default:
            break;
        }

        float P = err * kp;
        params->integrale_totale += (err * DELTA_T) + ((last_err - err) * (DELTA_T)) / 2; //Rajout de l'intégrale actuelle à l'intégrale totale
        float I = params->integrale_totale * ki; //Calcul du terme I
        float D = ((err - last_err) / DELTA_T) * kd; //Calcul du terme D

        float PID = P + I + D;
        //Prévention d'une puissance > 100 ou < 0
        if (PID > 100) {
            PID = 100;
        }
        if (PID < 0) {
            PID = 0;
        }
        return PID;
    }
}