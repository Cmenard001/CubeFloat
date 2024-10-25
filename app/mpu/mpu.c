#include "mpu.h"

#include "MPU6050/stm32g4_mpu6050.h"
#include "stm32g4_systick.h"

#include <stdio.h>
#include <stdint.h>

#define TIME_BETWEEN_MPU_READS 10 //ms

static MPU6050_t DataStruct;
static angular_speed_t angular_speed = 0;

void mpu_init()
{
    MPU6050_Result_t result = MPU6050_Init(&DataStruct, GPIOA, GPIO_PIN_1, MPU6050_Device_0, MPU6050_Accelerometer_2G, MPU6050_Gyroscope_2000s);
    if (result != MPU6050_Result_Ok)
    {
        switch (result)
        {
            case MPU6050_Result_DeviceNotConnected:
                printf("MPU6050 not connected\n");
                break;
            case MPU6050_Result_DeviceInvalid:
                printf("MPU6050 invalid\n");
                break;
            default:
                printf("MPU6050 unknown error\n");
                break;
        }
        while (1);
    }
}

void mpu_process()
{
    static uint32_t last_read_time = 0;
    static angle_t last_angle = 0;
    if (BSP_systick_get_time_us() - last_read_time > TIME_BETWEEN_MPU_READS * 1000)
    {
        last_read_time = BSP_systick_get_time_us();
        angle_t angle = mpu_get_angle();
        angular_speed = (angle - last_angle) / TIME_BETWEEN_MPU_READS;
        last_angle = angle;
    }
}

#include <stdio.h>

angle_t mpu_get_angle()
{
    MPU6050_Result_t result = MPU6050_ReadAll(&DataStruct);
    if (result != MPU6050_Result_Ok)
    {
        printf("MPU6050 read error\n");
        return 0;
    }
    angle_t angle = PI_INT * atan2(DataStruct.Accelerometer_X, DataStruct.Accelerometer_Y) + 25000;
    return angle;
}

angular_speed_t mpu_get_angular_speed()
{
    return angular_speed;
}
