#include "releve.h"

FT_HANDLE initUSB() {
    FT_HANDLE descr;
    FT_STATUS ftStatus = FT_Open(0, &descr);

    
    if(ftStatus == FT_OK) {
        printf("descr1: %p\n", descr);
        return descr;
    } else {
        printf("Echec de l'initialisation\n");
        return NULL;
    }
}

temp_t releve(FT_HANDLE descr) {
    
    temp_t temp;
    temp.exterieure = 0;
    temp.interieure = 0;

    unsigned char RxBuffer[256] = {0};
    int i, SOTint, SOText;

    FT_STATUS ftStatus;
    DWORD RxBytes = 6;
    DWORD BytesReceived = 0;

    ftStatus = FT_Open(0, &descr);
    
    if(ftStatus != FT_OK) { // FT_Open failed
        return temp; 
    }

    ftStatus = FT_Read(descr,RxBuffer,RxBytes,&BytesReceived);
    
    if (ftStatus == FT_OK && BytesReceived == RxBytes) {
        // FT_Read OK
        // printf("\n--Read success\n");

        /*for(i=0 ; i < (int)(sizeof(RxBuffer) / sizeof(RxBuffer[0])) ; i++) {
            printf("RxBuffer[%d] : %u\t", i, RxBuffer[i]);
        }

        printf("\n");*/

        switch (RxBuffer[0] >> 4) {
            case 0:
                SOText = ( ((RxBuffer[0] & 0x0F) << 8) | ((RxBuffer[1] & 0x0F ) << 4) | (RxBuffer[2] & 0x0F) );
                SOTint = ( ((RxBuffer[3] & 0x0F) << 8) | ((RxBuffer[4] & 0x0F ) << 4) | (RxBuffer[5] & 0x0F) );
                printf("0 : ");
                break;
            case 1:
                SOText = ( ((RxBuffer[1] & 0x0F) << 8) | ((RxBuffer[0] & 0x0F ) << 4) | (RxBuffer[5] & 0x0F) );
                SOTint = ( ((RxBuffer[2] & 0x0F) << 8) | ((RxBuffer[3] & 0x0F ) << 4) | (RxBuffer[4] & 0x0F) );
                printf("1 : ");
                break;
            case 2:
                SOText = ( ((RxBuffer[4] & 0x0F) << 8) | ((RxBuffer[5] & 0x0F ) << 4) | (RxBuffer[0] & 0x0F) );
                SOTint = ( ((RxBuffer[1] & 0x0F) << 8) | ((RxBuffer[2] & 0x0F ) << 4) | (RxBuffer[3] & 0x0F) );
                printf("2 : ");
                break;
            case 8:
                SOText = ( ((RxBuffer[3] & 0x0F) << 8) | ((RxBuffer[4] & 0x0F ) << 4) | (RxBuffer[5] & 0x0F) );
                SOTint = ( ((RxBuffer[0] & 0x0F) << 8) | ((RxBuffer[1] & 0x0F ) << 4) | (RxBuffer[2] & 0x0F) );
                printf("8 : ");
                break;
            case 9:
                SOText = ( ((RxBuffer[2] & 0x0F) << 8) | ((RxBuffer[3] & 0x0F ) << 4) | (RxBuffer[4] & 0x0F) );
                SOTint = ( ((RxBuffer[5] & 0x0F) << 8) | ((RxBuffer[0] & 0x0F ) << 4) | (RxBuffer[1] & 0x0F) );
                printf("9 : ");
                break;
            case 10:
                SOText = ( ((RxBuffer[1] & 0x0F) << 8) | ((RxBuffer[2] & 0x0F ) << 4) | (RxBuffer[3] & 0x0F) );
                SOTint = ( ((RxBuffer[4] & 0x0F) << 8) | ((RxBuffer[5] & 0x0F ) << 4) | (RxBuffer[0] & 0x0F) );
                printf("10 : ");
                break;
        }

        //printf("SOTint : %d\n", SOTint);
        //printf("SOText : %d\n", SOText);
        
        temp.interieure = (-39.64 + 0.04*SOTint);
        temp.exterieure = (-39.64 + 0.04*SOText);

        printf("temp.interieure : %f\n", temp.interieure);
        printf("temp.exterieure : %f\n", temp.exterieure);
    } else {
        // FT_Read Failed
        printf("Read failed\n");
    }

    FT_Close(descr);
    
    return temp;
}