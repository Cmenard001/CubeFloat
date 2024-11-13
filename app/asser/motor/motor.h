#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdint.h>

/**
 * @brief Power supply of the motor (mV)
 */
#define MOTOR_POWER_SUPPLY 20000 // mV

/**
 * @brief Voltage type
 * @note The unit of the voltage_t type is mV
 * @note The voltage can be negative to reverse the motor
 */
typedef int32_t voltage_t;

/**
 * @brief Initialize the motor module
 *
 */
void motor_init();

/**
 * @brief Process main of the motor module
 *
 * @param voltage The voltage to apply to the motor
 */
void motor_set_voltage(voltage_t voltage);

/**
 * @brief Get the voltage of the motor
 *
 * @return voltage_t The voltage of the motor in mV
 */
voltage_t motor_get_voltage();

#endif
