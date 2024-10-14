#ifndef __MATHS_ANGLE_H__
#define __MATHS_ANGLE_H__

#include <math.h>
#include <stdint.h>

/**
 * @brief Angle type
 * @see PI_INT It's the unit of the angle_t type
 * @note The range of the angle is [-PI_INT ; PI_INT]
 * @warning This type cannot represent a multiple of turn
 * @warning An angle cannot be negative with this type
 * @see full_angle_t for a type that can represent a multiple of turn
 * @note We can use overflow to make a modulo operation
 */
typedef int16_t angle_t;

/**
 * @brief Full angle type
 * @see PI_INT It's the unit of the full_angle_t type
 * @note This type can represent a multiple of turn
 * @note An angle can be negative with this type
 * @see angle_t for a type that cannot represent a multiple of turn
 */
typedef int32_t full_angle_t;

/**
 * @brief Unit of the angle_t and full_angle_t types
 * @see angle_t and full_angle_t
 */
#define PI_INT (1<<(sizeof(angle_t)*8-1))
// #define PI_INT (32768)

/**
 * @brief Function to convert a full angle to an angle in degree
 *
 * @param angle The full angle to convert
 * @return int16_t The angle in degree
 */
int16_t angle_to_deg(full_angle_t angle);

/**
 * @brief Function to convert an angle in degree to a full angle
 *
 * @param angle The angle in degree to convert
 * @return full_angle_t The full angle
 */
full_angle_t deg_to_angle(int16_t angle);

#endif
