#include "visualisationC.h"
/**
 * Ecrit la puissance dans le fichier data.txt en tout ou rien
 * Les températures doivent avoir été préalablement écrites
 * @param la puissance en %
 */
void visualisationC(float puissance_f) {
   if (access(".verrouData", F_OK) != -1) { // Si le fichier .verrouData existe
      printf("Verrou présent, impossible d'ouvrir le fichier");
      return;
   } else {
      FILE *fpVerrou = fopen(".verrouData", "w"); // Création du verrou
      fclose(fpVerrou);

      FILE *fp = fopen("data.txt",
                        "a"); // Ouverture du fichier data.txt en mode append
      if (fp == NULL) {
         printf("Echec de l'ouverture du fichier");
         return;
      }

      if (puissance_f == 0) {
         fprintf(fp, "false");
      } else {
         fprintf(fp, "true");
      }

      fclose(fp);
      remove(".verrouData"); // Suppression du verrou
   }
}
