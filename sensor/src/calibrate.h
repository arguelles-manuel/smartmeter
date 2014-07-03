#ifndef CALIBRATE_H
#define CALIBRATE_H

/* Placa de sensado I */
#ifdef  BOARD_ONE
#define G_SHUNT     20                          // 1/Rshunt = 1/0.05 (1/ohm)
#define R_DIV1      840000                      // R1+R2 en div. resistivo de entrada (ohm)
#define R_DIV2      478                         // R3 en div. resistivo de entrada (ohm)
#define G_DIV       (R_DIV2+R_DIV1)/(R_DIV2)    // Ganancia divisor resistivo de entrada
#define V_REF       2.461                       // Vref de optoacoplador (volt)
#define OFFSET_IN_V 498                         // offset entrada de tensión
#define OFFSET_IN_I 498                         // offset entrada de corriente

/* Placa de sensado II (con relé) */
#elif   defined BOARD_TWO
#define G_SHUNT     10                          // 1/Rshunt = 1/0.1 (1/ohm)
#define R_DIV1      857000                      // R1+R2 en div. resistivo de entrada (ohm)
#define R_DIV2      496.1                       // R3 en div. resistivo de entrada (ohm)
#define G_DIV       (R_DIV2+R_DIV1)/(R_DIV2)    // Ganancia divisor resistivo de entrada
#define V_REF       2.45                        // Vref de optoacoplador (volt)
#define OFFSET_IN_V 499                         // offset entrada de tensión
#define OFFSET_IN_I 499                         // offset entrada de corriente
#endif

#define G_OPT       V_REF/0.512                 // Ganancia optoacoplador
#define G_ADC       1024/2.5                    // Ganancia ADC

/* Conversiones lectura ADC */
#define KV          G_DIV/(G_OPT*G_ADC)         // a Volts
#define KI          G_SHUNT/(G_ADC*G_OPT)       // a Ampere
#define KP          KV*KI                       // a Watt

#endif // CALIBRATE_H