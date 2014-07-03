#ifndef STRUCTS_H
#define STRUCTS_H

/** Valores previos para la actualizaci�n del algoritmo de Goertzel. */
typedef struct
{
    short prev;     // s[n-1]
    short prev2;    // s[n-2]
} goertzel_state_t;

/** Variables de trabajo de un determinado canal. */
struct channel_parms_s
{
    short sample;               // Muestra actual (sin valor de VDC)
    goertzel_state_t harm_1;    // Valores previos para frec. fundamental
    goertzel_state_t harm_3;    // Valores previos para 3� arm�nico
    goertzel_state_t harm_5;    // Valores previos para 5� arm�nico
    //long pow_1;     // Potencia frec. fundamental
    //long pow_2;     // Potencia 3� arm�nico
    //long pow_3;     // Potencia 5� arm�nico
};

/** Variables de trabajo para el calculo de los par�metros de la fase. Se
    actualizan en cada muestra tomada de los canales de tensi�n y corriente. */
struct phase_working_parms_s
{
    long act_power_count;       // Suma de t�rminos de potencia activa
    unsigned long v_rms_count;  // Suma de t�rminos de tensi�n RMS
    unsigned long i_rms_count;  // Suma de t�rminos de corriente RMS
    struct channel_parms_s voltage;    // Canal de tensi�n
    struct channel_parms_s current;    // Canal de corriente
};

/** Par�metros calculados (definitivos) de la fase. */
// TODO: ver tipo de dato. Puede que lo env�e en Q15. ver precisi�n de cada
// medici�n.
struct phase_readings_s
{
    double v_rms;           // Tensi�n RMS
    double i_rms;           // Corriente RMS
    double act_power;       // Potencia activa
    double app_power;       // Potencia aparente
    double energy;          // Energ�a activa
    double power_factor;    // Factor de potencia
    double v_thd_3;         // Pot. relativa 3� arm�nico con respecto a fundamental
    double v_thd_5;         // Pot. relativa 5� arm�nico con respecto a fundamental
    double i_thd_3;
    double i_thd_5;
};

#endif //STRUCTS_H