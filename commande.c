#include "commande.h"

void commande(FT_HANDLE descr, float cmd)
{
    FT_STATUS ftStatus;
    DWORD BytesWritten;

    char TxBuffer[1]; // Contains data to write to device

    int puis = (cmd / 100) * 127;

    // printf("Puissance(prc) : %f\n", cmd);
    // printf("Puissance : %d\n", puis);

    ftStatus = FT_Open(0, &descr);

    if (ftStatus != FT_OK) {
        // FT_Open failed
        return;
    } else {
        if (puis) {
            TxBuffer[0] = puis /*&~ (1<<7)*/;
        } else {
            TxBuffer[0] = (char)0;
        }

        ftStatus = FT_Write(descr, TxBuffer, sizeof(TxBuffer), &BytesWritten);

        if (ftStatus == FT_OK) {
            // printf("FT_Write OK\n");
        } else {
            printf("FT_Write Failed\n");
        }
    }

    FT_Close(descr);

    return;
}