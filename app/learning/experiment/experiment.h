#ifndef __EXPERIMENT_H__
#define __EXPERIMENT_H__

#include "learning/model/const_slot.h"
#include "learning/success/success.h"
#include <stdint.h>

typedef enum
{
    EXPERIMENT_STATE_DISABLED,
    EXPERIMENT_STATE_IN_PROGRESS,
    EXPERIMENT_STATE_FINISHED
} experiment_state_t;

typedef struct
{
    const_slot_t slot;
    success_t success;
    experiment_state_t state;
    uint32_t start_time;
} experiment_t;

/**
 * @brief Function to initialize an experiment
 *
 * @param experiment The experiment to initialize
 * @param slot The slot to use
 * @param success The success to use
 */
void experiment_init(experiment_t *experiment, const_slot_t *slot, success_t *success);

/**
 * @brief Function to start an experiment
 *
 * @param experiment The experiment to run
 * @return experiment_state_t The state of the experiment
 */
void experiment_start(experiment_t *experiment);

/**
 * @brief Function to process the experiment every 1ms
 *
 * @param experiment The experiment to process
 * @note This function must be called every 1ms during the experiment
 */
void experiment_process_1ms(experiment_t *experiment);

/**
 * @brief Function to check if the experiment is finished
 *
 * @param experiment The experiment to check
 * @return experiment_state_t The state of the experiment
 */
experiment_state_t is_experiment_finished(experiment_t *experiment);

#endif
