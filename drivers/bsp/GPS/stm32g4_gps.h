/**
 *******************************************************************************
 * @file	stm32g4_gps.h
 * @author	Nirgal			&& Luc Hérault
 * @date	1 févr. 2018	&& Juin 2024 --> portage sur g431
 * @brief	Module pour utiliser le GPS
 *******************************************************************************
 */

#ifndef GPS_H_
#define GPS_H_
#include "config.h"
#if USE_GPS
#include "stm32g4_utils.h"

typedef struct
{
	uint16_t 	id;
	uint32_t 	time;		//[HHMMSS]
	uint32_t 	seconds;	//[sec since 0:00:00]
	double 		latitude_rad;		//rad
	double 		longitude_rad;		//rad
	double		latitude_deg;		//deg
	double		longitude_deg;		//deg
	int16_t		lat_degrees;	//Partie entière des degrés
	double		lat_minutes;	//Minutes d'angle, avec décimales
	int16_t		long_degrees;	//Partie entière des degrés
	double		long_minutes;	//Minutes d'angle, avec décimales
	bool		north;
	bool 		east;
	uint16_t	ground_speed;
	uint32_t 	date32;
	uint8_t checksum;
}gps_datas_t;

typedef enum
{
	NO_TRAME_RECEIVED = 0,	//Une trame est en cours de réception
	CHECKSUM_INVALID,
	TRAME_INVALID,
	TRAME_UNKNOW,			//Une trame inconnue a été reçue
	TRAME_GPRMC,			//Une trame GPRMC a été reçue
	TRAME_GPGGA				//Une trame GPGGA a été reçue
}nmea_frame_e;

nmea_frame_e BSP_GPS_process_rx(uint8_t c, gps_datas_t * gps_datas);
void BSP_GPS_test(void);
void BSP_GPS_demo(void);

#endif //USE_GPS
#endif /* GPS_H_ */

