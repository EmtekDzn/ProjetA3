#include "releve.h"

temp_t releve() {
    
    // Initialisation des temperatures
    temp_t temp;
    temp.exterieure = 0;
    temp.interieure = 0;

    unsigned char RxBuffer[256] = {0}; // Buffer dans lequel on va recuperer les données
    int SOTint, SOText;

    FT_STATUS ftStatus;
    FT_HANDLE handle;
    DWORD RxBytes = 6; // Nombre d'octets que l'on souhaite acquérir
    DWORD BytesReceived = 0; // Nombre d'octets recus

    ftStatus = FT_Open(0, &handle); // Ouvre l'appareil et retourne un support d'accès
    
    if(ftStatus != FT_OK) { // FT_Open failed
        return temp; 
    }

    ftStatus = FT_Read(handle,RxBuffer,RxBytes,&BytesReceived); // Lecture des données envoyées par l'appareil
    
    if (ftStatus == FT_OK && BytesReceived == RxBytes) { // Si la lecture a fonctionné et que le nombre d'octets reçus est le bon

        switch (RxBuffer[0] >> 4) { // On regarde quel octet est le premier a avoir ete recu et on calcule les SOT avec les bons octets
                                    // (cf format SOT : les octets arrivent dans les l'ordre les uns a la suite des autres)
            case 0: // Octet recu : octet 1 Text
                SOText = ( ((RxBuffer[0] & 0x0F) << 8) | ((RxBuffer[1] & 0x0F ) << 4) | (RxBuffer[2] & 0x0F) );
                SOTint = ( ((RxBuffer[3] & 0x0F) << 8) | ((RxBuffer[4] & 0x0F ) << 4) | (RxBuffer[5] & 0x0F) );
                printf("0 : ");
                break;
            case 1: // Octet recu : octet 2 Text
                SOText = ( ((RxBuffer[5] & 0x0F) << 8) | ((RxBuffer[0] & 0x0F ) << 4) | (RxBuffer[1] & 0x0F) );
                SOTint = ( ((RxBuffer[2] & 0x0F) << 8) | ((RxBuffer[3] & 0x0F ) << 4) | (RxBuffer[4] & 0x0F) );
                printf("1 : ");
                break;
            case 2: // Octet recu : octet 3 Text
                SOText = ( ((RxBuffer[4] & 0x0F) << 8) | ((RxBuffer[5] & 0x0F ) << 4) | (RxBuffer[0] & 0x0F) );
                SOTint = ( ((RxBuffer[1] & 0x0F) << 8) | ((RxBuffer[2] & 0x0F ) << 4) | (RxBuffer[3] & 0x0F) );
                printf("2 : ");
                break;
            case 8: // Octet recu : octet 1 Tint
                SOText = ( ((RxBuffer[3] & 0x0F) << 8) | ((RxBuffer[4] & 0x0F ) << 4) | (RxBuffer[5] & 0x0F) );
                SOTint = ( ((RxBuffer[0] & 0x0F) << 8) | ((RxBuffer[1] & 0x0F ) << 4) | (RxBuffer[2] & 0x0F) );
                printf("8 : ");
                break;
            case 9: // Octet recu : octet 2 Tint
                SOText = ( ((RxBuffer[2] & 0x0F) << 8) | ((RxBuffer[3] & 0x0F ) << 4) | (RxBuffer[4] & 0x0F) );
                SOTint = ( ((RxBuffer[5] & 0x0F) << 8) | ((RxBuffer[0] & 0x0F ) << 4) | (RxBuffer[1] & 0x0F) );
                printf("9 : ");
                break;
            case 10:// Octet recu : octet 3 Tint
                SOText = ( ((RxBuffer[1] & 0x0F) << 8) | ((RxBuffer[2] & 0x0F ) << 4) | (RxBuffer[3] & 0x0F) );
                SOTint = ( ((RxBuffer[4] & 0x0F) << 8) | ((RxBuffer[5] & 0x0F ) << 4) | (RxBuffer[0] & 0x0F) );
                printf("10 : ");
                break;
            default:
        }

        // Calcul des temperatures en degres
        temp.interieure = (-39.64 + 0.04*SOTint);
        temp.exterieure = (-39.64 + 0.04*SOText);

        // Affichage des temperatures en console
        printf("temp.interieure : %f\n", temp.interieure);
        printf("temp.exterieure : %f\n", temp.exterieure);
    } else {
        // FT_Read Failed
        printf("Read failed\n");
    }

    FT_Close(handle); // Fermeture de l'appareil
    
    return temp;
}