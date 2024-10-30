#include "experiment.h"

#include "macro.h"
#include "stm32g4_systick.h"
#include "mpu/mpu.h"

#include <stdbool.h>
#include <stdint.h>

#define TIME_MIN_EXPERIMENT 1000000 // 1 second
#define ANGLE_GROUND_TOLERANCE (PI_INT / 16)
#define ANGLE_GROUND_MIN (-PI_INT / 4 + ANGLE_GROUND_TOLERANCE)
#define ANGLE_GROUND_MAX (PI_INT / 4 - ANGLE_GROUND_TOLERANCE)

/**
 * @brief Function to check if the experiment is finished
 *
 * @param experiment The experiment to check
 * @return true If the experiment is finished
 * @return false If the experiment is not finished
 */
static bool is_experiment_finished(experiment_t *experiment, uint32_t start_time);
static bool is_experiment_finished(experiment_t *experiment, uint32_t start_time)
{
    // Check if the cube is on ground
    angle_t angle = mpu_get_angle();
    if (angle < ANGLE_GROUND_MIN || angle > ANGLE_GROUND_MAX)
    {
        return false;
    }
    if (BSP_systick_get_time_us() - start_time < TIME_MIN_EXPERIMENT)
    {
        return false;
    }
    return true;
}

/**
 * @brief Function to try to asser the cube
 *
 * @param experiment The experiment to to use
 */
static void try_asser_cube(experiment_t *experiment);
static void try_asser_cube(experiment_t *experiment)
{
    angle_t angle = mpu_get_angle();
    angular_speed_t angular_speed = mpu_get_angular_speed();
    voltage_t last_voltage = motor_get_voltage();

    // Calculate the voltage to apply to the motor
    voltage_t voltage = const_slot_calc(&experiment->slot, angle, angular_speed, last_voltage);

    // Apply the voltage to the motor
    motor_set_voltage(voltage);
}

void experiment_init(experiment_t *experiment, const_slot_t *slot, success_t *success)
{
    // Make a copy of the slot and success
    experiment->slot = *slot;
    experiment->success = *success;
}

experiment_state_t experiment_run(experiment_t *experiment)
{
    experiment_state_t to_return = EXPERIMENT_STATE_IN_PROGRESS;

    CREATE_MAE(experiment_mae_t, INIT, IN_PROGRESS, FINISHED);

    static uint32_t start_time = 0;

    switch(state)
    {
        case INIT:
            start_time = BSP_systick_get_time_us();
            state = IN_PROGRESS;
            break;

        case IN_PROGRESS:
            // Try to asser the cube
            try_asser_cube(experiment);
            if (is_experiment_finished(experiment, start_time))
            {
                state = FINISHED;
            }
            break;

        case FINISHED:
            // Reset the MAE and return the finished state
            to_return = EXPERIMENT_STATE_FINISHED;
            RESET_MAE();
            break;
    }

    return to_return;
}
