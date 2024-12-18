#ifndef __MPU_H__
#define __MPU_H__

#include "maths/maths_angle.h"

/**
 * @brief Function to initialize the MPU
 */
void mpu_init();

/**
 * @brief Function to get the angle from the MPU
 * @note The angle is relative to the vertical axis
 *
 * @return angle_t
 */
angle_t mpu_get_angle();

/**
 * @brief Function to get the angular speed from the MPU
 *
 * @return angular_speed_t
 */
angular_speed_t mpu_get_angular_speed();

#endif
