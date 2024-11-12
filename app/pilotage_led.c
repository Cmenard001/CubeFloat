/*
 * pilotage_led.c
 *
 *  Created on: 1 oct. 2024
 *      Author: victo
 */
#include "pilotage_led.h"
#include "WS2812/stm32g4_ws2812.h"
#include "MPU6050/stm32g4_mpu6050.h"
#include <math.h>
#include <stdio.h>
#include "mpu/mpu.h"
#include "stm32g4_systick.h"

#define ABS(X) (X > 0 ? X : -X)

static color_t tab_LED[8][8];

void pilotage_led_init()
{
    //BSP_WS2812_demo();
    BSP_WS2812_init();
}

void def_tab_LED(uint8_t x, uint8_t y, color_t color)
{
    if (x>8 || y>8)
    {
        return;
    } 
    if (x<0 || y<0)
    {
        return;
    }
    tab_LED[x][y]= color;
}

uint8_t dist_droite_pixel(angle_t angle, uint8_t x, uint8_t y )
{
    int8_t coord_x = 2*x-7;
    int8_t coord_y = 2*y-7;
    angle_t teta = rad_to_angle(atanf((float)coord_y/coord_x)) - angle;
    // teta = rad_modulo(teta);
    float calc_sin = sinf(angle_to_rad(teta));
    uint8_t dist = ABS(calc_sin)*sqrt((coord_x*coord_x) + (coord_y*coord_y));
    return dist;
}

void droite_TAB(angle_t angle) 
{
    for (uint8_t x = 0; x<8; x++)
    {
        for (uint8_t y = 0; y<8; y++)
        {
            uint8_t dist = dist_droite_pixel(angle, x, y);
            if (dist < 1)
            {
                tab_LED[x][y].color32 = WS2812_COLOR_LIGHT_RED;
            }
            else
            {
                tab_LED[x][y].color32 = WS2812_COLOR_BLACK;
            }
        }
    }
}
void afficher_matrice(void)
{
    uint32_t pixels[64];
    for (uint8_t x = 0; x < 8; x++)
    {
        for (uint8_t y = 0; y < 8; y++)
        {
            uint8_t index = x * 8 + y;
            pixels[index] = tab_LED[x][y].color32;
        }
    }
    BSP_WS2812_display(pixels, 64);
    HAL_Delay(50);
}

void process_main_pilotage_led(void)
{
    static uint32_t previous_time = 0;
    uint32_t current_time = BSP_systick_get_time_us();
    if (current_time - previous_time >= 100000)
    {
        previous_time = current_time;
        angle_t angle = mpu_get_angle();
        droite_TAB(angle);
        afficher_matrice();
    }
}
