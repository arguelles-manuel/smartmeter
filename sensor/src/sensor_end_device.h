#ifndef SENSOR_END_DEVICE_H
#define SENSOR_END_DEVICE_H

// MACROS ----------------------------------------------------------------------
#define IS_MESSAGE_CLUSTER()        (AF_INCOMING_MESSAGE_CLUSTER() == MESSAGE_CLUSTER)
#define CONNECT_LOAD()              (P2OUT &= ~RELAY)   // TODO: verificar
#define DISCONNECT_LOAD()           (P2OUT |= RELAY)
#define IS_LOAD_CONNECTED()         (!(P2IN & RELAY))
#define TOGGLE_LOAD_CONNECTION()    (P2OUT ^= RELAY)

// DEFINICIONES ----------------------------------------------------------------

// MSP430F2274
#define MCLK_FREQ           8000000
#define SMCLK_FREQ          MCLK_FREQ/2

#define SAMPLE_FREQ         2000        // frecuencia de muestreo (Hz)
#define N_SAMPLES           2000        // numero de muestras tomadas
#define BUF_LEN             120         // tama�o buffer de muestras (40 muestras/ciclo)

#define ACHAN_V             INCH_2      // canal anal�gico de tensi�n
#define ACHAN_I             INCH_3      // canal anal�gico de corriente
#define RELAY               BIT4        // P2.4 (output)

// Flag de estados de la aplicaci�n
#define STATE_IDLE                          0x01
#define STATE_ZNP_STARTUP                   0x02
#define STATE_INIT_MEASURE                  0x04
#define STATE_CALC_PARAMETERS               0x08
#define STATE_SEND_REPORT_MSG               0x10
#define STATE_INCOMING_MSG                  0x20
#define STATE_CHECK_ALARM_FLAGS             0x40
#define STATE_ERROR                         0x80

#define ZNP_RESTART_DELAY                   5   // seg
#define ZNP_RESTART_DELAY_IF_MESSAGE_FAIL   5
#define REPORT_MSG_RETRY_DELAY              1
#define MEASURE_PERIOD                      5
#define LOAD_RECONNECTION_DELAY             8

#define MAX_REPORT_MSG_RETRY    3       // m�x. intentos de env�o de reporte

// Flags de alarmas
#define ALARM_FLAG_OVERVOLTAGE      0x0001
#define ALARM_FLAG_UNDERVOLTAGE     0x0002
#define ALARM_FLAG_V_THD_3          0x0004
#define ALARM_FLAG_V_THD_5          0x0008
#define ALARM_FLAG_NEGATIVE_POWER   0x0010
#define ALARM_FLAG_MAX_ENERGY       0x0020
#define ALARM_FLAG_MAX_LOAD         0x0040

// VARIABLES EXTERNAS ----------------------------------------------------------
extern unsigned char znpBuf[100];       // buffer para ZNP
extern signed int znpResult;            // resultado de operaciones ZNP

// FUNCIONES EXTERNAS ----------------------------------------------------------
extern void (*timerAIsr)(void);         // puntero a funci�n ISR del Timer A
extern void (*timerBIsr)(void);         // puntero a funci�n ISR del Timer B
extern void (*srdyIsr)(void);           // puntero a funci�n ISR de se�al SRDY
extern void (*buttonIsr)(void);         // puntero a funci�n ISR del bot�n

// VARIABLES LOCALES -----------------------------------------------------------
signed short v_buf[BUF_LEN];            // buffer muestras de tensi�n
signed short i_buf[BUF_LEN];            // buffer muestras de corriente
unsigned int state = 0;                 // flag de estados de la aplicaci�n
unsigned int stateFlags = 0;            // flags seteados durante los estados
unsigned int seqNumber = 0;             // n�mero de secuencia de paquetes
unsigned char reportRetry = 0;          // reintentos de envio de reporte
unsigned int vloFreq;                   // frecuencia del VLO
struct message_t outMsg;                // buffers de mensajes
struct message_t inMsg;
struct phase_working_parms_s phase;
struct phase_readings_s readings;
unsigned int samp_count;                // cantidad de muestras tomadas
char signal_sign;
char first_samp;
char sampling;

// FUNCIONES LOCALES -----------------------------------------------------------
void stateMachine();                    // ciclo principal de la aplicaci�n
void isrInitMeasure();                  // ISR iniciar medici�n
void isrSrdy();                         // ISR de SRDY
void isrZnpStartup();                   // ISR inicio de ZNP
void isrSendReport();                   // ISR enviar mensaje
void isrAdcTimerA();                    // ISR Timer A para muestreo
void isrToggleLoad();                   // ISR del bot�n
void isrReconnectLoad();                // ISR rel�
int initRetryTimerA(unsigned int sleepTime, void (*handler)(void));
int initTimerB(unsigned int seconds);
void initTimerAdc();                    // configura e inicia el Timer A para muestreo
void initAdc();                         // configura registros del ADC
char detectZeroCrossing();
void harmonics();

#endif //SENSOR_END_DEVICE