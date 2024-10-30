#ifndef __EXPERIMENT_H__
#define __EXPERIMENT_H__

#include "learning/model/const_slot.h"
#include "learning/success/success.h"

typedef struct
{
    const_slot_t slot;
    success_t success;
} experiment_t;

typedef enum
{
    EXPERIMENT_STATE_IN_PROGRESS,
    EXPERIMENT_STATE_FINISHED
} experiment_state_t;

void experiment_init(experiment_t *experiment, const_slot_t *slot, success_t *success);

/**
 * @brief Function to run an experiment
 *
 * @param experiment The experiment to run
 * @return experiment_state_t The state of the experiment
 */
experiment_state_t experiment_run(experiment_t *experiment);

#endif
