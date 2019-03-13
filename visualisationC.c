#include "visualisationC.h"
/**
 * Ecrit la puissance dans le fichier data.txt en tout ou rien
 * Les températures doivent avoir été préalablement écrites
 * @param la puissance en %
 */
void visualisationC(float puissance_f) {
    if (access(".verrouData", F_OK) != -1) { // Si le fichier .verrouData existe
        printf("visualisationC : Verrou présent, impossible d'ouvrir le fichier data\n");
    } else {
        FILE *fpVerrou = fopen(".verrouData", "w"); // Création du verrou
        fclose(fpVerrou);

        FILE *fp = fopen("data.txt", "r"); // Ouverture du fichier data.txt en mode read

        if (fp == NULL) {
            printf("visualisationC : Echec de l'ouverture du fichier data\n");
            return;
        }

        float temp1, temp2;
        fscanf(fp, "%f", &temp1);
        fscanf(fp, "%f", &temp2);
        fclose(fp);

        fp = fopen("data.txt", "w"); // Ouverture du fichier data.txt en mode write
        if (fp == NULL) {
            printf("visualisationC : Echec de la réouverture du fichier data\n");
            return;
        }
        fprintf(fp, "%.2f\n", temp1); //Recopie des températures déjà présentes
        fprintf(fp, "%.2f\n", temp2); //Recopie des températures déjà présentes

        if (puissance_f == 0) {
            fprintf(fp, "false"); //Écriture de l'état du chauffage
        } else {
            fprintf(fp, "true"); //Écriture de l'état du chauffage
        }

        fclose(fp);
        while (access(".verrouData", F_OK) != -1) { //Tant que le verrou existe
            remove(".verrouData"); // Suppression du verrou
        }
    }
}
