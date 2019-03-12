#include "consigne.h"

/**
 * Lit la valeur de la consigne dans le fichier consigne.txt
 * @param csgn valeur retournée si le verrou est présent
 */
float consigne(float csgn)
{
   if (access(".verrouConsigne", F_OK) != -1) { // Si le fichier .verrouData existe
      printf("Verrou present, impossible d'ouvrir le fichier consigne\n");
   } else {
      FILE *fpVerrou = fopen(".verrouConsigne", "w"); // Création du verrou
      fclose(fpVerrou);
 
      FILE *fp = fopen("consigne.txt", "r"); // Ouverture du fichier consigne.txt en mode read
      
      if (fp == NULL) {
         printf("Echec de l'ouverture du fichier\n");
         return csgn;
      }

      fscanf(fp, "%f", &csgn);

      fclose(fp);
      remove(".verrouConsigne"); // Suppression du verrou
   }

   return csgn;
}

