#include <string.h>
#include "message.h"
#include "../../Common/printf.h"
#include "../../Common/utilities.h"

/**
 * Imprime el mensaje en la consola. 
 * @param   im  el message_t a imprimir
 */
void printMessage(struct message_t* im) {
    // header
    printf("#%u MAC=", im->sequence);
    for (int j = 0; j < 8; j++) {
        printf("%02X", im->mac[j]);
        if (j != 7) printf(":");
    }
    printf(" type=%02X, lenData=%u: ", im->msgType, im->lenData);
    
    // data
    if (im->msgType == MSG_TYPE_REPORT)
    {
        double d;
        for (int i = 0; i < MSG_LEN_DATA_REPORT; i+=4)
        {
            memcpy(&d, &(im->data[i]), sizeof(d));
            // printf es small format!
            printf("[%i.%i] ", (int)d, (int)(d*100.0-(int)d*100));
        }
    }
    else if (im->msgType == MSG_TYPE_ALARM)
    {
        unsigned int flags;
        memcpy(&flags, &(im->data[0]), sizeof(flags));
        printf("[%04X] ", flags);
    }
    else
    {
        for (int i = 0; i < im->lenData; i++)
            printf("%04X ", im->data[i]);
    }
    printf("\r\n");
}

/**
 * Copia el mensaje como un stream de bytes a la ubicación de memoria apuntada
 * por destinationPtr. El número de bytes copiados es igual a getSizeOfInfoMessage().
 * @param   im              el mensaje a serializar
 * @param   destinationPtr  puntero a un región de memoria de al menos 
 *                          getSizeOfInfoMessage() bytes
 */
void serializeMessage(struct message_t* im, unsigned char* destinationPtr) {  
    // header
    *destinationPtr++ = im->sequence & 0xFF;  //LSB primero
    *destinationPtr++ = im->sequence >> 8;
    for (int i = 0; i < 8; i++)
        *destinationPtr++ = im->mac[i];
    *destinationPtr++ = im->msgType;
    *destinationPtr++ = im->lenData;
    // data
    for (int i = 0; i < im->lenData; i++)
        *destinationPtr++ = im->data[i];
}

/**
 * Crea un message_t a partir de un stream de bytes apuntado por source.
 * @param   source  puntero al comienzo del mensaje serializado
 * @return  un message_t con los datos parseados.
 * @todo verificar que lenData < MAX_DATA_MESSAGE
 */
struct message_t deserializeMessage(unsigned char* source) {
    unsigned char* sourcePtr = source;
    struct message_t im;
    // header
    im.sequence = CONVERT_TO_INT( (*sourcePtr), (*(sourcePtr+1)) );
    sourcePtr += 2;
    for (int i = 0; i < 8; i++)
        im.mac[i] = *sourcePtr++;
    im.msgType = *sourcePtr++;
    im.lenData = *sourcePtr++;
    // data
    for (int i = 0; i < im.lenData; i++)
        im.data[i] = *sourcePtr++;

    return im;
}

/**
 * @return la longitud del mensaje en bytes
 */
unsigned int getSizeOfMessage(struct message_t* im) { 
  return (LEN_HEADER + im->lenData);
}