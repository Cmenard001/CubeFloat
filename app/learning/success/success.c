#include "success.h"
#include "stm32g4_systick.h"
#include "mpu/mpu.h"
#include "macro.h"

#define MAX_ANGLE (PI_INT/2)

const float WEIGHT_OF_COEFFS[SUCCESS_ID_COUNT] =
{
    [SUCCESS_ID_DURATION]       = 1.0f,
    [SUCCESS_ID_OSCILLATION]    = 0.0f,
};

void success_init(success_t *success)
{
    for (int i = 0; i < SUCCESS_ID_COUNT; i++)
    {
        success->coeffs[i].coeff = 0.0f;
        success->coeffs[i].weight = WEIGHT_OF_COEFFS[i];
    }
    success->sum_angle = 0;
    success->nb_mesures = 0;
    success->start_time = 0;
}

void success_evaluate_process_1ms(success_t *success)
{
    angle_t angle = mpu_get_angle();
    success->sum_angle += ABS(angle);
    success->nb_mesures++;
}

void success_evaluate_start(success_t *success)
{
    success->start_time = BSP_systick_get_time_us();
}

void success_evaluate_end(success_t *success)
{
    uint32_t end_time = BSP_systick_get_time_us();
    success->coeffs[SUCCESS_ID_DURATION].coeff = (float)(end_time - success->start_time);

    if (success->sum_angle == 0)
    {
        success->coeffs[SUCCESS_ID_OSCILLATION].coeff = 0.0f;
    }
    else
    {
        success->coeffs[SUCCESS_ID_OSCILLATION].coeff = (float)(success->nb_mesures) / success->sum_angle;
    }
}

float success_get(success_t *success)
{
    float success_value = 0.0f;

    for (int i = 0; i < SUCCESS_ID_COUNT; i++)
    {
        success_value += success->coeffs[i].coeff * success->coeffs[i].weight;
    }

    return success_value;
}
