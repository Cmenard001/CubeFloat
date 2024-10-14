#include "maths_angle.h"

int16_t angle_to_deg(full_angle_t angle)
{
    return angle * 180 / PI_INT;
}

full_angle_t deg_to_angle(int16_t angle)
{
    return angle * PI_INT / 180;
}
