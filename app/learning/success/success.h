#ifndef __SUCCESS_H__
#define __SUCCESS_H__

#include "success_coeff.h"

#include <stdint.h>

/**
 * @brief Success of an experiment is mesured by :
 * - The duration of the experiment
 * - If the cube oscillates a lot or not
 * - If the cube is stable at the end of the experiment
 */

typedef enum
{
    SUCCESS_ID_DURATION,
    SUCCESS_ID_OSCILLATION,
    SUCCESS_ID_COUNT
} success_id_t;

typedef struct
{
    uint32_t start_time;
    uint64_t sum_angle;
    uint32_t nb_mesures;
    success_coeff_t coeffs[SUCCESS_ID_COUNT];
} success_t;

/**
 * @brief Function to initialize the success
 *
 * @param success Success to initialize
 */
void success_init(success_t *success);

/**
 * @brief Function to evaluate the success of an experiment
 *
 * @param success Success to evaluate
 * @note This function must be called every 1ms
 */
void success_evaluate_process_1ms(success_t *success);

/**
 * @brief Function to start the evaluation of the success of an experiment
 *
 * @param success Success to evaluate
 * @note This function must be called at the beginning of the experiment
 */
void success_evaluate_start(success_t *success);

/**
 * @brief Function to evaluate the success of an experiment
 *
 * @param success Success to evaluate
 * @note This function must be called at the end of the experiment
 */
void success_evaluate_end(success_t *success);

/**
 * @brief Function to get the success of an experiment
 *
 * @param success Success to get
 * @return The success of the experiment
 */
float success_get(success_t *success);

#endif
