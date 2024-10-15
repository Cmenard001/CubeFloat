#ifndef __ASSER_ANGLE_H__
#define __ASSER_ANGLE_H__

#include "maths/maths_angle.h"

/**
 * @brief Function to initialize the asser_angle
 */
void asser_angle_init();

/**
 * @brief Function to process the asser_angle
 * @note This function must be called in the main loop
 */
void asser_angle_process();

/**
 * @brief Function to set the target angle
 *
 * @param angle_t
 */
void asser_angle_set_target_angle(angle_t angle);

/**
 * @brief Function to get the target angle
 *
 * @return angle_t
 */
angle_t asser_angle_get_target_angle();

#endif
