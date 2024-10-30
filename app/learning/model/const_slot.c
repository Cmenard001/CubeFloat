#include "const_slot.h"

#include <math.h>

voltage_t experience_calc(const_slot_t *const_slot, angle_t angle, angular_speed_t angular_speed, voltage_t last_voltage)
{
    /*
        tension = a * (sinf(b*angle+c))^(-3)
            + d * (sinf(b*angle+c))^(-2)
            + g * sinf(b*angle+c)
            + h * (sinf(b*angle+c))^2
            + i * (sinf(b*angle+c))^3
            + j * angular_speed^2
            + k * angular_speed
            + l*last_tension^(-3)
            + m*last_tension^(-2)
            + n*last_tension
            + o*last_tension^2
            + p*last_tension^3
            + q
    */
    float *a = &const_slot->const_slot[CONST_ID_A];
    float *b = &const_slot->const_slot[CONST_ID_B];
    float *c = &const_slot->const_slot[CONST_ID_C];
    float *d = &const_slot->const_slot[CONST_ID_D];
    float *g = &const_slot->const_slot[CONST_ID_G];
    float *h = &const_slot->const_slot[CONST_ID_H];
    float *i = &const_slot->const_slot[CONST_ID_I];
    float *j = &const_slot->const_slot[CONST_ID_J];
    float *k = &const_slot->const_slot[CONST_ID_K];
    float *l = &const_slot->const_slot[CONST_ID_L];
    float *m = &const_slot->const_slot[CONST_ID_M];
    float *n = &const_slot->const_slot[CONST_ID_N];
    float *o = &const_slot->const_slot[CONST_ID_O];
    float *p = &const_slot->const_slot[CONST_ID_P];
    float *q = &const_slot->const_slot[CONST_ID_Q];

    float sin_angle = sinf(*b * angle + *c);

    voltage_t to_return
        = *a * powf(sin_angle, -3)
        + *d * powf(sin_angle, -2)
        + *g * sin_angle
        + *h * powf(sin_angle, 2)
        + *i * powf(sin_angle, 3)
        + *j * powf(angular_speed, 2)
        + *k * angular_speed
        + *l * powf(last_voltage, -3)
        + *m * powf(last_voltage, -2)
        + *n * last_voltage
        + *o * powf(last_voltage, 2)
        + *p * powf(last_voltage, 3)
        + *q;

    return to_return;
}
