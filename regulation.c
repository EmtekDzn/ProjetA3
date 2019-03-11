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
    for (int i = 1; i < nT; i++) {
        cmd = regulation(regul, csgn, tabT[i], tabT[i-1]);
    }
    return cmd;
}

/**
 * Renvoie la puissance en % ou tout-ou-rien
 * @param regul 1 = tout-ou-rien, 2 = PID
 * @param csgn la température de consigne
 * @param la température intérieure
 * @param la température intérieure précédente
 * @return la commande
 */
float regulation(int regul, float csgn, float tempInt, float lastTempInt) {
    if (regul == 1) {
        if (csgn > tempInt) {
            return 1;
        }
        return 0;
    } else {
        float et = csgn - tempInt;
        float lastEt = csgn - lastTempInt;
        float P = et * KP;
        float I = 0;//TODO
        float D = ((et - lastEt)/(DELTA_T))*KD;
        return P+I+D;
    }
}