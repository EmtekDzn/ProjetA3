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

    printf("descr2: %p\n", descr);
    
    temp_t temp;
    char RxBuffer[256] = {0};
    int i = 0;

    FT_STATUS ftStatus;
    DWORD EventDWord = 0;
    DWORD TxBytes = 0;
    DWORD RxBytes = 6;
    DWORD BytesReceived = 0;

    ftStatus = FT_Open(0, &descr);
    
    if(ftStatus != FT_OK) {
        // FT_Open failed
        return;
    }

    ftStatus = FT_Read(descr,RxBuffer,RxBytes,&BytesReceived);
    
    if (ftStatus == FT_OK) {
        if(BytesReceived == RxBytes) {
            // FT_Read OK
            printf("\n--Read success\n");

            /*for(i=0 ; i < (int)(sizeof(RxBuffer) / sizeof(RxBuffer[0])) ; i++) {
                printf("RxBuffer[%d] : %u\t", i, RxBuffer[i]);
            }

            printf("\n");*/

            int SOTint = ( ((RxBuffer[0] & 0x0F) << 8) | ((RxBuffer[1] & 0x0F ) << 4) | (RxBuffer[2] & 0x0F) );
            int SOText = ( ((RxBuffer[3] & 0x0F) << 8) | ((RxBuffer[4] & 0x0F ) << 4) | (RxBuffer[5] & 0x0F) );

            printf("SOTint : %d\n", SOTint);
            printf("SOText : %d\n", SOText);
            
            temp.interieure = (-39.64 + 0.04*SOTint);
            temp.exterieure = (-39.64 + 0.04*SOText);

            printf("temp.interieure : %f\n", temp.interieure);
            printf("temp.exterieure : %f\n", temp.exterieure);
        } else {
            printf("Timeout");
        }
    } else {
        // FT_Read Failed
        printf("Read failed\n");
    }

    FT_Close(descr);
    
    return temp;
}