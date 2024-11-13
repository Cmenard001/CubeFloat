/**
 *******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
 */

#include "config.h"
#include "stm32g4_sys.h"

#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include "asser/asser_current/asser_current.h"
#include "asser/motor/motor.h"
#include "asser/asser_angle/asser_angle.h"
#include "mpu/mpu.h"

#include <stdio.h>

#define UART_BAUDRATE 115200

/**
  * @brief  Point d'entrée de votre application
  */
int main(void)
{
	/* Cette ligne doit rester la première de votre main !
	 * Elle permet d'initialiser toutes les couches basses des drivers (Hardware Abstraction Layer),
	 * condition préalable indispensable à l'exécution des lignes suivantes.
	 */
	HAL_Init();

	/* Initialisation des périphériques utilisés dans votre programme */
	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID, UART_BAUDRATE);

	/* Indique que les printf sont dirigés vers l'UART2 */
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	/*
		Display a message on the terminal to indicate that the
		card is still alive ^^ (or that the card to correctly reset)
	*/
	printf("Start...\n");

	/* Initialization of cube modules */
	motor_init();
	motor_set_voltage(0);
	asser_current_init();
	asser_current_set_order(0);
	mpu_init();
	asser_angle_init();

	/* Tâche de fond, boucle infinie, Infinite loop,... quelque soit son nom vous n'en sortirez jamais */
	while (1)
	{

	}
}
