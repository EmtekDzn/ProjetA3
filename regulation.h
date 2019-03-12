#include "define.h"

#define KP 1
#define KD 0.1
#define KI 0.1
#define DELTA_T 10
/**
 * @struct params_regul
 * Contient des paramètres pour la régulation
 */
typedef struct {
    int mode; // Mode de régulation (TOR/PID)
    float consigne; // Température de consigne
    float integrale_totale; // Somme des intégrales (pour le I)
} params_regul;

float regulationTest(int regul, float csgn, float *tabT, int nT);
float regulation(params_regul *params, float err, float last_err);
