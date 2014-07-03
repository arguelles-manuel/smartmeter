#ifndef MESSAGE_H
#define MESSAGE_H

#define MESSAGE_CLUSTER         0x0007
#define MAX_DATA_MESSAGE        40
#define LEN_HEADER              12        // longitud (en bytes) del HEADER

// Tipos de mensaje
#define MSG_TYPE_REPORT         0x01      // reporte enviado por nodo sensor
#define MSG_TYPE_ALARM          0x02      // alarma enviada por el coordinador
#define MSG_TYPE_INFO           0x03

// Cantidad de bytes en campo data[]
#define MSG_LEN_DATA_REPORT     40      
#define MSG_LEN_DATA_ALARM      2
#define MSG_LEN_DATA_NOTIFY     2

// Offset del dato en data[]
#define MSG_VRMS_FIELD          0       // REPORT, todos los datos son de tipo
#define MSG_IRMS_FIELD          1*4     // double de 4 bytes
#define MSG_PACT_FIELD          2*4
#define MSG_PAPP_FIELD          3*4
#define MSG_ENERGY_FIELD        4*4
#define MSG_FP_FIELD            5*4
#define MSG_V_THD_3_FIELD       6*4
#define MSG_V_THD_5_FIELD       7*4
#define MSG_I_THD_3_FIELD       8*4
#define MSG_I_THD_5_FIELD       9*4
#define MSG_ALARM_FLAGS_FIELD   0       // ALARM, único dato de tipo uint16


struct message_t {
    // HEADER
    unsigned int sequence;      // nº de secuencia del paquete
    unsigned char mac[8];       // dirección MAC del nodo sensor (end-device)
    unsigned char msgType;      // tipo de mensaje (reporte, alarma, etc.)
    unsigned char lenData;      // cantidad de bytes en data[]
    // DATA
    unsigned char data[MAX_DATA_MESSAGE];   // datos en little-endian
};

void printMessage(struct message_t* im);
void serializeMessage(struct message_t* im, unsigned char* destinationPtr);
struct message_t deserializeMessage(unsigned char* source);
unsigned int getSizeOfMessage(struct message_t* im);

#endif