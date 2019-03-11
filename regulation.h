#include "define.h"

#define KP 1
#define KD 0.1
#define KI 0.1
#define DELTA_T 10
float regulationTest(int regul, float csgn, float *tabT, int nT);
float regulation(int regul, float csgn, float tempInt, float lastTempInt);
