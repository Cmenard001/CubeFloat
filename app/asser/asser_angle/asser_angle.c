#include "asser_angle.h"

#include "maths/maths_angle.h"
#include "asser/asser_current/asser_current.h"
#include "asser/motor/motor.h"
#include "mpu/mpu.h"
#include "stm32g4_systick.h"
#include <stdio.h>

#define CUBE_MASS 830 // g
#define GRAVITY_CONST 10 // mN/g or mm/ms^2
#define LEVER_ARM_LENGTH 80 // mm
#define K_SPEED 100 // 1/ms
#define ASSER_TIME 100 // ms
#define KT_MOTOR (1000) // mN·mm/mA
#define INERTIA_MOMENT 1 // g/mm^2

static angle_t target_angle = 0;

void asser_angle_init()
{
    target_angle = 0;
}

void asser_angle_process()
{
    angle_t angle = mpu_get_angle();
    angular_speed_t angular_speed = mpu_get_angular_speed();
    angle_t angle_error = target_angle - angle;
    // TODO : Documentation
    int32_t moment_to_stay_up = - CUBE_MASS * GRAVITY_CONST * LEVER_ARM_LENGTH * sinf((float)angle/PI_INT);
    int32_t moment_to_go_to_speed = (K_SPEED * angle_error - angular_speed) * INERTIA_MOMENT / ASSER_TIME;
    int32_t target_current32 = (moment_to_stay_up + moment_to_go_to_speed) / KT_MOTOR;
    current_t target_current;
    if(target_current32 > 32767)
    {
        target_current = 32767;
    }
    else if(target_current32 < -32767)
    {
        target_current = -32767;
    }
    else
    {
        target_current = (current_t)target_current32;
    }
    asser_current_set_order(target_current);
    // Print som debugs values every 1000ms
    static uint32_t last_print_time = 0;
    if (BSP_systick_get_time_us() - last_print_time > 500000)
    {
        last_print_time = BSP_systick_get_time_us();
        printf("angle : %d, angular_speed : %d, angle_error : %d, accel_to_stay_up : %d, accel_to_go_to_speed : %d, target_current : %d, voltage : %d\n", angle, angular_speed, angle_error, moment_to_stay_up, moment_to_go_to_speed, target_current, motor_get_voltage());
    }
}

void asser_angle_set_target_angle(angle_t angle)
{
    target_angle = angle;
}

angle_t asser_angle_get_target_angle()
{
    return target_angle;
}
