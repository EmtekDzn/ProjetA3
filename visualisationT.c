#include "visualisationT.h"
/**
 * Ecrit les températures (intérieure et extérieure) dans le fichier data.txt
 * @param myTemp les températures
 */
void visualisationT(temp_t myTemp) {
    if (access(".verrouData", F_OK) != -1) { // Si le fichier .verrouData existe
        printf("visualisationT : Verrou présent, impossible d'ouvrir le fichier data\n");
    } else {
        FILE *fpVerrou = fopen(".verrouData", "w"); // Création du verrou
        fclose(fpVerrou);

        FILE *fp = fopen("data.txt", "r");
        if (fp == NULL) { //Si l'ouverture du fichier a échoué
            printf("visualisationT : Echec de l'ouverture du fichier data\n");
            return;
        }

        char puis = 0;
        while (puis != 't' && puis != 'f') { //Tant qu'on a pas trouvé la première lettre de la commande chauffage
            fscanf(fp, "%c", &puis);         //Lire le caractère courant (et avancer le curseur de 1)
        }

        fclose(fp);
        fp = fopen("data.txt", "w");
        if (fp == NULL) { //Si l'ouverture du fichier a échoué
            printf("visualisationC : Echec de la réouverture du fichier data\n");
            return;
        }

        fprintf(fp, "%.2f\n", myTemp.exterieure); //Écriture des températures
        fprintf(fp, "%.2f\n", myTemp.interieure); //Écriture des températures

        if (puis == 't') {
            fprintf(fp, "true"); //Recopie de l'état du chauffage
        } else {
            fprintf(fp, "false"); //Recopie de l'état du chauffage
        }

        fclose(fp);
        while (access(".verrouData", F_OK) != -1) { //Tant que le verrou existe
            remove(".verrouData");                  //Suppression du verrou
        }
    }
}