#include "commande.h"

void commande(FT_HANDLE descr, float cmd) {
    FT_STATUS ftStatus;
    DWORD BytesWritten;
    
    char TxBuffer[256]; // Contains data to write to device

    int puis = (cmd/100)*127;

    printf("Puissance(prc) : %f\n", cmd);
    printf("Puissance : %d\n", puis);

    if(puis) {
        TxBuffer[0] = puis /*&~ (1<<7)*/;
    } else {
        TxBuffer[0] = (char)128;
    }

    ftStatus = FT_Write(descr, TxBuffer, sizeof(TxBuffer), &BytesWritten);
    
    if (ftStatus == FT_OK) {
        printf("FT_Write OK\n");
    } else {
        printf("FT_Write Failed\n");
    }

    return;
}