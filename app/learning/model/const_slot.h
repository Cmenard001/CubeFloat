#ifndef __CONST_SLOT_H__
#define __CONST_SLOT_H__

#include "maths/maths_angle.h"
#include "asser/asser_current/asser_current.h"
#include "asser/motor/motor.h"

/**
 * @brief Enumeration of id for each constant in a const slot
 * @see ./README.md for more details on model constants
 */
typedef enum
{
    CONST_ID_A,
    CONST_ID_B,
    CONST_ID_C,
    CONST_ID_D,
    CONST_ID_E,
    CONST_ID_F,
    CONST_ID_G,
    CONST_ID_H,
    CONST_ID_I,
    CONST_ID_J,
    CONST_ID_K,
    CONST_ID_L,
    CONST_ID_M,
    CONST_ID_N,
    CONST_ID_O,
    CONST_ID_P,
    CONST_ID_Q,
    CONST_ID_COUNT
} const_id_t;

typedef struct
{
    float const_slot[10];
} const_slot_t;

/**
 * @brief Function to calculate the voltage to apply to the motor
 * @see ./README.md for more details on model constants
 *
 * @param const_slot Slot of constants to use
 * @param angle Current angle of the cube mesured
 * @param angular_speed Current angular speed of the cube mesured
 * @param last_voltage Last voltage applied to the motor
 * @return voltage_t Voltage to apply to the motor
 */
voltage_t const_slot_calc(const_slot_t *const_slot, angle_t angle, angular_speed_t angular_speed, voltage_t last_voltage);

#endif
