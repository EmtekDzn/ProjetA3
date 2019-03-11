#include "visualisationT.h"
/**
 * Ecrit les températures (intérieure et extérieure) dans le fichier data.txt
 * @param myTemp les températures
 */
void visualisationT(temp_t myTemp) {
    if (access(".verrouData", F_OK) != -1) { // Si le fichier .verrouData existe
        printf("Verrou présent, impossible d'ouvrir le fichier");
        return;
    } else {
        FILE *fpVerrou = fopen(".verrouData", "w"); // Création du verrou
        fclose(fpVerrou);

        FILE *fp = fopen("data.txt", "r+");
        if (fp == NULL) {
            printf("Echec de l'ouverture du fichier");
            return;
        }
        float dummy1, dummy2;
        char puis;
        fscanf(fp, "%f", &dummy1);
        fscanf(fp, "%f", &dummy2);
        fseek(fp, 1, SEEK_CUR);
        fscanf(fp, "%c", &puis);

        rewind(fp);

        fprintf(fp, "%.2f\n", myTemp.exterieure);
        fprintf(fp, "%.2f\n", myTemp.interieure);
        if (puis == 't') {
            fprintf(fp, "true");
        }else{
            fprintf(fp, "false");
        }

        fclose(fp);
        remove(".verrouData"); // Suppression du verrou
    }
}