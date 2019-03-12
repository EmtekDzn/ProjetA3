#include "visualisationT.h"
/**
 * Ecrit les températures (intérieure et extérieure) dans le fichier data.txt
 * @param myTemp les températures
 */
void visualisationT(temp_t myTemp) {
    if (access(".verrouData", F_OK) != -1) { // Si le fichier .verrouData existe
        printf("Verrou present, impossible d'ouvrir le fichier data\n");
    } else {
        FILE *fpVerrou = fopen(".verrouData", "w"); // Création du verrou
        fclose(fpVerrou);

        FILE *fp = fopen("data.txt", "r+");
        if (fp == NULL) {
            printf("Echec de l'ouverture du fichier\n");
        }
        char puis = 0;
        while(puis != 't' && puis != 'f'){//Tant qu'on a pas trouvé la première lettre de la commande chauffage
            fscanf(fp, "%c", &puis);//Lire le caractère courant (et avancer le curseur de 1)
        } 

        fp = freopen(NULL, "w", fp);

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