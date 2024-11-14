#include "maths_angle.h"

int16_t angle_to_deg(full_angle_t angle)
{
    return angle * 180 / PI_INT;
}

full_angle_t deg_to_angle(int16_t angle)
{
    return angle * PI_INT / 180;
}

float rad_modulo(float angle)
{
    while (angle > PI_FLOAT)
    {
        angle -= 2*PI_FLOAT;
    }
    while (angle < -PI_FLOAT)
    {
        angle += 2*PI_FLOAT;
    }
    return angle;
}

float angle_to_rad(angle_t angle)
{
    angle = rad_modulo((float)angle * PI_FLOAT / (float)PI_INT);
    return angle;
}

angle_t rad_to_angle(float angle)
{
    return angle * PI_INT / PI_FLOAT;
}
