#include "success_coeff.h"

void success_coeff_init(success_coeff_t *coeff, float coeff_value, float weight_value)
{
    coeff->coeff = coeff_value;
    coeff->weight = weight_value;
}

void success_coeff_set_coeff(success_coeff_t *coeff, float coeff_value)
{
    coeff->coeff = coeff_value;
}
