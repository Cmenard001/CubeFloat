#ifndef __SUCCESS_COEFF_H__
#define __SUCCESS_COEFF_H__

typedef struct
{
    float coeff;
    float weight;
} success_coeff_t;

/**
 * @brief Function to initialize the success coefficient
 *
 * @param coeff Coefficient to initialize
 * @param coeff_value Value of the coefficient
 * @param weight_value Weight of the coefficient
 */
void success_coeff_init(success_coeff_t *coeff, float coeff_value, float weight_value);

/**
 * @brief Function to set the value of the coefficient
 *
 * @param coeff Coefficient to set
 * @param coeff_value Value of the coefficient
 */
void success_coeff_set_coeff(success_coeff_t *coeff, float coeff_value);

#endif
