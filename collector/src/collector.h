#ifndef COLLECTOR_APP_H
#define COLLECTOR_APP_H

/******************************************************************************
 * CONSTANTES
 */

// Definiciones para el stack de ZigBee
#define MY_PROFILE_ID               0xD7D7  /**< ZigBee Profile ID de la aplicación */
#define MY_ENDPOINT_ID              0xD7    /**< ZigBee End Point ID de la aplicación */
#define DEV_ID_SENSOR               1   /**< ID del dispositivo Sensor */
#define DEV_ID_COLLECTOR            2   /**< ID del dispositivo Colector/Coordinador */
#define DEVICE_VERSION_SENSOR       1   /**< Versión del dispositivo Sensor */
#define DEVICE_VERSION_COLLECTOR    1   /**< Versión del dispositivo Colector/Coordinador */

#define RX_BUF_LEN                  128 /**< Tamaño del buffer de RX de UART */

// Condiciones de alarmas
#define V_RMS_OVERVOLTAGE           220*(1+0.1) // 220V + 10%
#define V_RMS_UNDERVOLTAGE          220*(1-0.1) // 220V - 10%
#define V_THD_3_THRESHOLD           5           // % con respecto fundamental
#define V_THD_5_THRESHOLD           6           // % con respecto fundamental
#define I_RMS_MAX_LOAD              1.0         // Ampere
#define MAX_ENERGY_CONSUMPTION      100         // Joules = Watt * seg

#endif // COLLECTOR_APP_H