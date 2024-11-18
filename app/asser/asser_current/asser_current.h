/**
 * @file asser_current.h
 * @author Cyprien Menard
 * @brief Module to asserv the current of the motor
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __ASSER_CURRENT_H__
#define __ASSER_CURRENT_H__

#include <stdint.h>

/**
 * @brief Current type
 * @note The unit of the current_t type is mA
 */
typedef int32_t current_t;

/**
 * @brief Process moin of the current module
 * @note This function must be called every 1ms
 */
void asser_current_process_1ms();

/**
 * @brief Initialize the current module
 */
void asser_current_init();

/**
 * @brief Get the current
 * @return The current in mA
 */
current_t asser_current_get();

/**
 * @brief get thoe order given at the module
 * @param current The current in mA
 */
current_t asser_current_order_get();

/**
 * @brief Set an order to the current module
 * @param current The current in mA
 * @note The sign of the current impact the direction of the motor
 */
void asser_current_set_order(current_t current);

/**
 * @brief Test the current module
 *
 * @param current The current in mA to try to reach
 */
void asser_current_test(current_t current);

#endif
