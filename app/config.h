/**
 *******************************************************************************
 * @file 	config.h
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de configuration de votre projet sur carte NuclÃ©o STM32G431KB.
 * 			Permet d'activer les diffÃ©rents modules logiciels Ã  votre disposition.
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CONFIG_H_
#define CONFIG_H_


/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Defines -------------------------------------------------------------------*/
#define LED_GREEN_PIN 		GPIO_PIN_8
#define LED_GREEN_GPIO 		GPIOB

#define UART2_ON_PA3_PA2
#define UART1_ON_PA10_PA9

#define USE_BSP_TIMER		1
#define USE_BSP_EXTIT		1

#define USE_RTC				0

#define USE_ADC				1
	/* Configuration pour activer les entrÃ©es analogiques souhaitÃ©es */
	#define USE_IN1		0 //Broche correspondante: PA0
	#define USE_IN2		0 //Broche correspondante: PA1
	#define USE_IN3		1 //Broche correspondante: PA6
	#define USE_IN4		1 //Broche correspondante: PA7
	#define USE_IN10	0 //Broche correspondante: PF1 /!\ Broche indisponible sur g431 sauf si SB11 et pas SB10 (petits pads Ã  souder sur la carte)
	#define USE_IN13	1 //Broche correspondante: PA5
	#define USE_IN17	0 //Broche correspondante: PA4

#define USE_DAC				0

/*------------------Afficheurs------------------*/
#define USE_ILI9341			0 // écran TFT
#if USE_ILI9341
	#define USE_XPT2046			1
	#define USE_FONT7x10		1
	#define USE_FONT11x18		0
	#define USE_FONT16x26		0
#endif

#define USE_EPAPER			0 // e-paper (écran basse consommation)
#define USE_WS2812			1 // Matrice de led

/*------------------Capteurs------------------*/
#define USE_MPU6050			1 // Accéléromètre, Gyroscope
#define USE_APDS9960		0 // Capteur de mouvements, présence, couleurs
#define USE_BMP180			0 // Capteur de pression atmosphérique
#define USE_BH1750FVI		0 // Capteur de luminosité ambiante
#define USE_DHT11			0 // Capteur de température et d'humidité
#define USE_DS18B20			0 // Sonde de température
#define USE_YX6300			0 // Lecteur MP3
#define USE_MATRIX_KEYBOARD 0 // Clavier matriciel
#define USE_HCSR04			0 // Télémetre à ultrason
#define USE_GPS				0 // GPS
#define USE_LD19			0 // Lidar --> veuillez aussi activer USE_ILI9341, USE_XPT2046, USE_FONT7x10 et USE_FONT16x26 si vous voulez utiliser display_ld19.c
#define USE_NFC03A1			0 // Shield NFC
#define USE_VL53L0			0 // Télémetre laser de grande précision
#if USE_VL53L0
	#define VL53L0X_I2C			I2C1
	#define VL53_NB				1 // La version actuelle du driver ne peut traiter que 8 capteurs au maximum
	//Vous devez définir ci dessous autant de lignes VL_x que le nombre indiqué ci-dessus avec x allant de 0 Ã  VL53_NB-1
	#define VL_0				GPIOA, GPIO_PIN_0 // Pin de reset
	//#define VL_1				GPIOD, GPIO_PIN_3
	//#define VL_2				GPIOE, GPIO_PIN_10
#endif

/*------------------Expanders------------------*/
#define USE_MCP23017		0 // GPIO expander qui communique en i2C
#define USE_MCP23S17		0 // GPIO expander qui communique en SPI
#define USE_SD_CARD			0 // Carte SD pour lire/écrire des fichiers

/*------------------Actionneurs------------------*/
#define USE_MOTOR_DC		1

/*------------------Périphériques------------------*/

#if USE_MLX90614 || USE_MPU6050	|| USE_APDS9960	 || USE_BH1750FVI || USE_BMP180 || USE_MCP23017 || USE_VL53L0 // Liste des modules utilisants le pÃ©riphÃ©rique I2C
	#define USE_I2C				1
#else
	#ifndef USE_I2C
		#define USE_I2C				0
	#endif
#endif
#define I2C_TIMEOUT			5//ms

#if USE_ILI9341 || USE_SD_CARD || USE_MCP23S17 || USE_EPAPER // Liste des modules utilisants le périphérique SPI
	#define USE_SPI				1
#else
	#ifndef USE_SPI
		#define USE_SPI				0
	#endif
#endif

#define USE_TESTBOARD				0


#endif /* CONFIG_H_ */
