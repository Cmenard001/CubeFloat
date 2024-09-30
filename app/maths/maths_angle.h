#ifndef __MATHS_ANGLE_H__
#define __MATHS_ANGLE_H__

#include <math.h>
#include <stdint.h>

/**
 * @brief Angle type
 * @see PI_INT It's the unit of the angle_t type
 * @note The range of the angle is [0, 2*PI_INT)
 * @warning This type cannot represent a multiple of turn
 * @see full_angle_t for a type that can represent a multiple of turn
 * @note We can use overflow to make a modulo operation
 */
typedef uint16_t angle_t;

/**
 * @brief Full angle type
 * @see PI_INT It's the unit of the full_angle_t type
 * @note The range of the angle is [0, 2*PI_INT)
 * @note This type can represent a multiple of turn
 * @see angle_t for a type that cannot represent a multiple of turn
 */
typedef uint32_t full_angle_t;

/**
 * @brief Unit of the angle_t and full_angle_t types
 * @see angle_t and full_angle_t
 */
#define PI_INT (1<<(sizeof(angle_t)*8-1))
// #define PI_INT (32768)

#endif
