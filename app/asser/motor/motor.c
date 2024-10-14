#include "motor.h"

#include "stm32g4_timer.h"
#include "stm32g4_gpio.h"
#include "stm32g431xx.h"

/**
 * @brief Période du signal PWM, en microsecondes
 *
 */
#define	PWM_PERIOD	50

#define PWM_PIN_GPIOX GPIOA
#define PWM_PIN_NUMBER GPIO_PIN_8

#define WAY_PIN_GPIOX GPIOB
#define WAY_PIN_NUMBER GPIO_PIN_0

#define MOTOR_TIMER_ID TIMER1_ID
#define MOTOR_TIMER_CHANNEL TIM_CHANNEL_1

static voltage_t current_voltage;

void motor_init()
{
    GPIO_InitTypeDef GPIO_PWM_InitStruct = (GPIO_InitTypeDef){
        .Pin = PWM_PIN_NUMBER,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW
    };
    GPIO_InitTypeDef GPIO_WAY_InitStruct = (GPIO_InitTypeDef){
        .Pin = WAY_PIN_NUMBER,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW
    };
    HAL_GPIO_Init(PWM_PIN_GPIOX, &GPIO_PWM_InitStruct);
    HAL_GPIO_Init(WAY_PIN_GPIOX, &GPIO_WAY_InitStruct);
    BSP_TIMER_run_us(MOTOR_TIMER_ID, PWM_PERIOD, false);
    BSP_TIMER_enable_PWM(MOTOR_TIMER_ID, MOTOR_TIMER_CHANNEL, 0, false, false);
}

void motor_set_voltage(voltage_t voltage)
{
    current_voltage = voltage;
    int16_t duty = voltage * 1000 / MOTOR_POWER_SUPPLY;
    if (voltage >= 0)
    {
        HAL_GPIO_WritePin(WAY_PIN_GPIOX, WAY_PIN_NUMBER, GPIO_PIN_SET);
    }
    else
    {
        duty = -duty;
        HAL_GPIO_WritePin(WAY_PIN_GPIOX, WAY_PIN_NUMBER, GPIO_PIN_RESET);
    }
    BSP_TIMER_set_duty(MOTOR_TIMER_ID, MOTOR_TIMER_CHANNEL, duty);
}

voltage_t motor_get_voltage()
{
    return current_voltage;
}
