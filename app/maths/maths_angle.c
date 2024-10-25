#include "maths_angle.h"

#define PI_FLOAT 3.14159265358979323846

int16_t angle_to_deg(full_angle_t angle)
{
    return angle * 180 / PI_INT;
}

full_angle_t deg_to_angle(int16_t angle)
{
    return angle * PI_INT / 180;
}

float angle_to_rad(angle_t angle)
{
    return angle * PI_FLOAT / PI_INT;
}

angle_t rad_to_angle(float angle)
{
    return angle * PI_INT / PI_FLOAT;
}
