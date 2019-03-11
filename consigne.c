#include "consigne.h"

/**
 * Lit la valeur de la consigne dans le fichier consigne.txt
 * @param retour si verrou 
 */
float consigne(float csgn)
{
   if (access(".verrouData", F_OK) != -1) { // Si le fichier .verrouData existe
      printf("Verrou présent, impossible d'ouvrir le fichier");
   } else {
      FILE *fpVerrou = fopen(".verrouData", "w"); // Création du verrou
      fclose(fpVerrou);
 
      FILE *fp = fopen("consigne.txt", "r"); // Ouverture du fichier consigne.txt en mode read
      
      if (fp == NULL) {
         printf("Echec de l'ouverture du fichier");
         return csgn;
      }

      fscanf(fp, "%f", &csgn);

      fclose(fp);
      remove(".verrouData"); // Suppression du verrou
   }

   return csgn;
}

