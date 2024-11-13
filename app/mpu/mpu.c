#include "mpu.h"

#include "MPU6050/stm32g4_mpu6050.h"
#include "stm32g4_systick.h"

#include <stdio.h>
#include <stdint.h>

static MPU6050_t DataStruct;

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

angle_t mpu_get_angle()
{
    MPU6050_Result_t result = MPU6050_ReadAccelerometer(&DataStruct);
    if (result != MPU6050_Result_Ok)
    {
        printf("MPU6050 read error\n");
        return 0;
    }
    /*
        Compute the angle of the robot
        The angle is in radian
        The range of the angle is [-PI_INT ; PI_INT]
        The angle is computed with the accelerometer
        The angle is computed with the formula:
        angle = atan2(-accelerometer_x, accelerometer_y)
        (See a trigonometry course to understand this formula)
        The angle is then converted to the range [-PI_INT ; PI_INT]
    */
    // TODO : Remove the offset to put it in asser_angle
    angle_t angle = PI_INT * atan2f(DataStruct.Accelerometer_X, DataStruct.Accelerometer_Y) / 2 - 27200;
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
    /*
        Gyroscope values are in degrees per second
        We convert them to radians per second
    */
    angular_speed_t angular_speed = PI_INT * DataStruct.Gyroscope_Z / 180;
    return angular_speed;
}
