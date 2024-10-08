#include "mpu.h"

#include "MPU6050/stm32g4_mpu6050.h"

#include <stdio.h>

static MPU6050_t DataStruct;

void mpu_init()
{
    MPU6050_Result_t result = MPU6050_Init(&DataStruct, NULL, GPIO_PIN_0, MPU6050_Device_0, MPU6050_Accelerometer_2G, MPU6050_Gyroscope_2000s);
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

#include <stdio.h>

angle_t mpu_get_angle()
{
    MPU6050_Result_t result = MPU6050_ReadAll(&DataStruct);
    if (result != MPU6050_Result_Ok)
    {
        printf("MPU6050 read error\n");
        return 0;
    }
    angle_t angle = PI_INT * atan2(DataStruct.Accelerometer_X, DataStruct.Accelerometer_Y) + 3*PI_INT/4;
    return angle;
}
