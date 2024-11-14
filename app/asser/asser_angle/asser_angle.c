#include "asser_angle.h"

#include "maths/maths_angle.h"
#include "asser/asser_current/asser_current.h"
#include "asser/motor/motor.h"
#include "mpu/mpu.h"
#include "stm32g4_systick.h"
#include <stdio.h>

/**
 * @brief Constants for the calculation of the current to apply to the motor
 * @see asser_angle_process_1ms
 */
#define CUBE_MASS 878 // g
#define GRAVITY_CONST 10 // mN/g or mm/ms^2
#define LEVER_ARM_LENGTH 80 // mm
#define K_SPEED 1 // ms^-1
#define ASSER_TIME 10 // ms
#define KT_MOTOR 100 // mN·mm/mA
#define INERTIA_MOMENT 100 // g/mm^2

#define TARGET_ANGLE 27200

/**
 * @brief Target angle
 */
static angle_t target_angle = 0;

void asser_angle_init()
{
    target_angle = TARGET_ANGLE;
}

void asser_angle_process_main()
{
    angle_t angle = mpu_get_angle();
    angular_speed_t angular_speed = mpu_get_angular_speed();
    angle_t angle_error = target_angle - angle;
    angular_speed_t angular_speed_target = K_SPEED * angle_error;
    angular_speed_t angular_speed_error = angular_speed_target - angular_speed;
    /*
        Explanation of the calculation of the current instructions:

        First, the moment is calculated to keep the cube in its current angle.
        In static, the sum of the moments is zero, so the time necessary to maintain the cube
        In its current angle is equal to the time of gravity of the cube.

        P = m * g
        We calculate the moment of gravity of the cube as a function of the current angle of the cube.
        M = P * l * sin (angle)
        <==> m = m * g * l * sin (angle)
        with :
        - M: Cube's moment of gravity
        - M: Cube mass
        - G: Constant of severity
        - L: length of the lever arm
        - Angle: cube angle with vertical

        However, we do not want the cube to remain in its current angle,
        Otherwise the wheel will accelerate indefinitely until you reach the maximum speed and the cube will fall.
        So we want the cube to move.

        We therefore define a target angular speed as a function of the target angle.
        Ω = K * angle_error
        Thus, when the target angle is reached, the target angular speed is zero.
        So theoretically, the cube cannot oscillate around the target angle.

        We then calculate the necessary moment to reach the angular speed target in X seconds.
        M = in * Ω / Δt
        <==> m = in * k * angle_error / Δt
        with :
        - M: moment required to reach the target angular speed
        - In: cube inertia moment
        - Ω: target angular speed
        - Δt: time to reach the target angular speed

        We are the two moments to obtain the total moment necessary to reach the target angle.
        M = m * g * l * sin (angle) + in * k * angle_error / Δt

        Finally, we calculate the necessary current to obtain the total moment.
        I = m / kt
        with :
        - I: current necessary to reach the target angle
        - KT: engine torque constant
    */
    int32_t moment_to_stay_up = - CUBE_MASS * GRAVITY_CONST * LEVER_ARM_LENGTH * sinf(angle_to_rad(angle));
    int32_t moment_to_go_to_speed = angular_speed_error * INERTIA_MOMENT / ASSER_TIME;
    current_t target_current = (moment_to_stay_up + moment_to_go_to_speed) / KT_MOTOR;

    // Set the current to the motor
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
