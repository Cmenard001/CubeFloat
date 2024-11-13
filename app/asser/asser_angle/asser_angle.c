#include "asser_angle.h"

#include "maths/maths_angle.h"
#include "asser/asser_current/asser_current.h"
#include "asser/motor/motor.h"
#include "mpu/mpu.h"
#include "stm32g4_systick.h"
#include <stdio.h>

#define CUBE_MASS 878 // g
#define GRAVITY_CONST 10 // mN/g or mm/ms^2
#define LEVER_ARM_LENGTH 80 // mm
#define K_SPEED 1 // ms^-1
#define ASSER_TIME 10 // ms
#define KT_MOTOR 100 // mN·mm/mA
#define INERTIA_MOMENT 100 // g/mm^2

static angle_t target_angle = 0;

void asser_angle_init()
{
    target_angle = 0;
    BSP_systick_add_callback_function(&asser_angle_process_1ms);
}

void asser_angle_process_1ms()
{
    angle_t angle = mpu_get_angle();
    angular_speed_t angular_speed = mpu_get_angular_speed();
    angle_t angle_error = target_angle - angle;
    angular_speed_t angular_speed_target = K_SPEED * angle_error;
    angular_speed_t angular_speed_error = angular_speed_target - angular_speed;
    // TODO : Documentation
    int32_t moment_to_stay_up = - CUBE_MASS * GRAVITY_CONST * LEVER_ARM_LENGTH * sinf(angle_to_rad(angle));
    int32_t moment_to_go_to_speed = angular_speed_error * INERTIA_MOMENT / ASSER_TIME;
    current_t target_current = (moment_to_stay_up + moment_to_go_to_speed) / KT_MOTOR;
    asser_current_set_order(target_current);
    // Print som debugs values sometimes
    static uint32_t last_print_time = 0;
    if (BSP_systick_get_time_us() - last_print_time > 500000)
    {
        last_print_time = BSP_systick_get_time_us();
        printf("angle : %d, ", angle);
        printf("target_angle : %d, ", (int)target_angle);
        printf("angular_speed : %d, ", (int)angular_speed);
        printf("angular_speed_target : %d, ", (int)angular_speed_target);
        printf("moment_to_stay_up : %d, ", (int)moment_to_stay_up);
        printf("moment_to_go_to_speed : %d, ", (int)moment_to_go_to_speed);
        printf("target_current : %d ", (int)target_current);
        printf("mesured current : %d\n", (int)asser_current_get());
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
