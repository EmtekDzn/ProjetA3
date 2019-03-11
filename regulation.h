#include "define.h"

#define KP 1
#define KD 0.1
#define KI 0.1
#define DELTA_T 10

typedef struct {
    int mode;
    float consigne;
    float somme_erreurs;
} params_regul;

float regulationTest(int regul, float csgn, float *tabT, int nT);
float regulation(params_regul *params, float err, float last_err);
