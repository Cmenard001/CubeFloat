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

#include <stdio.h>

angle_t mpu_get_angle()
{
    MPU6050_Result_t result = MPU6050_ReadAccelerometer(&DataStruct);
    if (result != MPU6050_Result_Ok)
    {
        printf("MPU6050 read error\n");
        return 0;
    }
    angle_t angle = PI_INT * atan2f(DataStruct.Accelerometer_X, DataStruct.Accelerometer_Y) / 2 + 12000;
    return angle;
}

angular_speed_t mpu_get_angular_speed()
{
    MPU6050_Result_t result = MPU6050_ReadGyroscope(&DataStruct);
    if (result != MPU6050_Result_Ok)
    {
        printf("MPU6050 read error\n");
        return 0;
    }
    // Gyroscope values are in degrees per second
    // We convert them to radians per second
    angular_speed_t angular_speed = PI_INT * DataStruct.Gyroscope_Z / 180;
    return angular_speed;
}
