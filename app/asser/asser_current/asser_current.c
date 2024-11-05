#include "asser_current.h"
#include "stm32g4_adc.h"
#include "asser/motor/motor.h"
#include "stm32g4_systick.h"

#include <stdint.h>

#define K_VOLTAGE 5000 // mV.A^-1.ms^-1
#define VOLTAGE_MAX (MOTOR_POWER_SUPPLY)
#define VOLTAGE_MIN (-MOTOR_POWER_SUPPLY)
#define CURRENT_OFFSET 50 // mA
#define MAX_CURRENT 2500 // mA

#define DIRECTION(A) ((A) > 0 ? true : false)

/**
 * @brief Order of current
 */
static current_t current_order = 0;

static void asser_current();
static void asser_current()
{
    voltage_t voltage = motor_get_voltage();
    // Get the current
    current_t current = asser_current_get();
    current_t current_error = current_order - current;
    // Compute the new voltage
    voltage += K_VOLTAGE * current_error / 1000;

    // Check the voltage limit
    if (voltage > VOLTAGE_MAX)
    {
        voltage = VOLTAGE_MAX;
    }
    else if (voltage < VOLTAGE_MIN)
    {
        voltage = VOLTAGE_MIN;
    }
    // Set the new voltage
    motor_set_voltage(voltage);
}

void asser_current_init()
{
    BSP_ADC_init();
    motor_init();
    BSP_systick_add_callback_function(&asser_current_process_1ms);
}

void asser_current_process_1ms()
{
    asser_current();
}

current_t asser_current_get()
{
    // Mesure the current on the probe
    uint32_t adc_mesure = BSP_ADC_getValue(ADC_1);
    // Convert the value to a current
    // The probe mesure 1V/A
    // The ADC is on 12 bits
    // The ADC is on 3.3V
    // The current return is in mA
    // So the formula is :
    current_t current = (current_t)((((int32_t)adc_mesure)*3300)/4096) - CURRENT_OFFSET;
    if (motor_get_voltage() < 0)
    {
        current = -current;
    }
    return current;
}

current_t asser_current_order_get()
{
    return current_order;
}

void asser_current_set_order(current_t current)
{
    current_order = current;
    if(current_order > MAX_CURRENT)
    {
        current_order = MAX_CURRENT;
    }
    else if(current_order < -MAX_CURRENT)
    {
        current_order = -MAX_CURRENT;
    }
}
