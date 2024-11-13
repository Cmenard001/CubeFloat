#include "asser_current.h"
#include "stm32g4_adc.h"
#include "asser/motor/motor.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4xx_hal_gpio.h"

#include <stdint.h>

#define K_VOLTAGE 3000 // mV.A^-1.ms^-1
#define VOLTAGE_INCREMENT 0 // mV.ms^-1
#define VOLTAGE_MAX (MOTOR_POWER_SUPPLY)
#define VOLTAGE_MIN (-MOTOR_POWER_SUPPLY)
#define MAX_CURRENT 10000 // mA

// Current probe
// ADC for compute current
#define CURRENT_ADC_WAY_1 ADC_4
#define CURRENT_ADC_WAY_2 ADC_13
#define NB_ECHANTILLON 10

/**
 * @brief Order of current
 */
static current_t current_order = 0;

typedef struct
{
    int32_t adc_mesure_sum;
    int32_t adc_mesure_tab[NB_ECHANTILLON];
    int32_t adc_mesure_index;
} avg_value_t;

static avg_value_t avg_adc_values[2] =
{
    {
        .adc_mesure_sum = 0,
        .adc_mesure_tab = {0},
        .adc_mesure_index = 0
    },
    {
        .adc_mesure_sum = 0,
        .adc_mesure_tab = {0},
        .adc_mesure_index = 0
    }
};

static void asser_current();
static void asser_current()
{
    voltage_t voltage = motor_get_voltage();
    // Get the current
    current_t current = asser_current_get();
    current_t current_error = current_order - current;
    // Compute the new voltage
    voltage_t voltage_increment = current_error < 0 ? -VOLTAGE_INCREMENT : VOLTAGE_INCREMENT;
    voltage += K_VOLTAGE * current_error / 1000 + voltage_increment;

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
    BSP_systick_add_callback_function(&asser_current_process_1ms);
}

void asser_current_process_1ms()
{
    int32_t adc_mesure_1 = BSP_ADC_getValue(CURRENT_ADC_WAY_1);
    int32_t adc_mesure_2 = BSP_ADC_getValue(CURRENT_ADC_WAY_2);

    avg_adc_values[0].adc_mesure_sum -= avg_adc_values[0].adc_mesure_tab[avg_adc_values[0].adc_mesure_index];
    avg_adc_values[0].adc_mesure_sum += adc_mesure_1;
    avg_adc_values[0].adc_mesure_tab[avg_adc_values[0].adc_mesure_index] = adc_mesure_1;
    avg_adc_values[0].adc_mesure_index = (avg_adc_values[0].adc_mesure_index + 1) % NB_ECHANTILLON;

    avg_adc_values[1].adc_mesure_sum -= avg_adc_values[1].adc_mesure_tab[avg_adc_values[1].adc_mesure_index];
    avg_adc_values[1].adc_mesure_sum += adc_mesure_2;
    avg_adc_values[1].adc_mesure_tab[avg_adc_values[1].adc_mesure_index] = adc_mesure_2;
    avg_adc_values[1].adc_mesure_index = (avg_adc_values[1].adc_mesure_index + 1) % NB_ECHANTILLON;

    asser_current();
}

current_t asser_current_get()
{
    // Mesure the current on the probe
    current_t current = (avg_adc_values[1].adc_mesure_sum - avg_adc_values[0].adc_mesure_sum) / 10;
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
