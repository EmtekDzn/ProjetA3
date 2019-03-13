#include "commande.h"

/**
 * Fonction de commande envoyant la puissance du chauffage à la carte
 * @param cmd : Puissance en %
 */
void commande(float cmd)
{
    FT_STATUS ftStatus;
    DWORD BytesWritten;
    FT_HANDLE handle;

    char TxBuffer[1]; // Buffer contenant les données a ecrire sur la carte

    int puis = (cmd / 100) * 127; // Calcul de la puissance

    ftStatus = FT_Open(0, &handle); // Ouvre l'appareil et retourne un support d'accès.

    if (ftStatus != FT_OK) { // Si l'ouverture a échoué
        return; // On quitte
    } else { // Sinon
        if (puis) { // Si la puissance n'est pas nulle
            TxBuffer[0] = puis; // On l'écrit dans le buffer sur le premier octet
        } else {
            TxBuffer[0] = (char)0; // Sinon on écrit 0
        }

        ftStatus = FT_Write(handle, TxBuffer, sizeof(TxBuffer), &BytesWritten); // Puis on l'écrit sur la carte

        if (ftStatus == FT_OK) {
            printf("FT_Write OK\n");
        } else {
            printf("FT_Write Failed\n");
        }
    }

    FT_Close(handle); // On ferme le support

    return;
}