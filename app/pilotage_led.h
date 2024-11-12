/*
 * pilotage_led.h
 *
 *  Created on: 1 oct. 2024
 *      Author: victo
 */

#ifndef PILOTAGE_LED_H_
#define PILOTAGE_LED_H_

#include "config.h"
#include <stdint.h>
#include "maths/maths_angle.h"

enum
{
    COLOR_RESERVED,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
};

typedef union
{
    uint32_t color32;
    uint8_t color8[4];
} color_t;

/**
* @brief cette fonction permet d'initialiser les LEDs.
*/
void pilotage_led_init();

/**
* @brief Définit la couleur d'une LED dans le tableau.
* @param x Coordonnée x de la LED (doit être entre 0 et 7).
* @param y Coordonnée y de la LED (doit être entre 0 et 7).
* @param color Couleur à attribuer à la LED, représentée par un `color_t`.
*/
void def_tab_LED(uint8_t x, uint8_t y, color_t color);

/**
* @brief cette fonction allume ou non chaque pixels selon le résultat de la fonction dist_droite_pixel().
* @param angle Angle de la ligne en degrés.
*/
void droite_TAB(angle_t angle);

/**
* @brief cette fonction calcule la distance entre chaque pixel et la droite du tableau définie par l'angle du mpu.
* @param angle Angle de la ligne en degrés.
* @param x Coordonnée x du pixel.
* @param y Coordonnée y du pixel.
* @return uint8_t Distance du pixel par rapport à la ligne.
*/
uint8_t dist_droite_pixel(angle_t angle, uint8_t x, uint8_t y );

/**
* @brief cette fonction sert à afficher la matrice LEDs avec le contenu du tableau 'tab_LED'.
* Cette fonction convertit les valeurs du tableau `tab_LED` en une matrice de 64 pixels, 
* puis envoie les données au driver WS2812 pour afficher les couleurs sur les LEDs.
*/
void afficher_matrice(void);

/**
*@brief cette fonction permet d'exécuter afficher_matrice()  et de récupérer l'angle du mpu toutes les 100ms.
*/
void process_main_pilotage_led(void);

#endif /* PILOTAGE_LED_H_ */