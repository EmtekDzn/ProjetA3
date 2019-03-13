#include "define.h"
/*Constantes PID pour tests initaires*/
#define KP_UNIT 1
#define KD_UNIT 0.1
#define KI_UNIT 0.1
/*Constantes PID pour tests dans simulation*/
#define KP_SIMU 100
#define KD_SIMU 0.1
#define KI_SIMU 0.01
/*Constantes PID pour tests via USB*/
#define KP_USB 1
#define KD_USB 0.1
#define KI_USB 0.1

#define DELTA_T 10
/**
 * @struct params_regul
 * Contient des paramètres pour la régulation
 */
typedef struct {
    int mode; // Mode de régulation (TOR/PID)
    float consigne; // Température de consigne
    float integrale_totale; // Somme des intégrales (pour le I)
}params_regul;

float regulationTest(int regul, float csgn, float *tabT, int nT);
float regulation(int mode_PID, params_regul *params, float err, float last_err);
