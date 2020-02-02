/*
    A library for Grove - 3-Axis Digital Accelerometer ±2g to 16g Ultra-low Power(BMA400)

    Copyright (c) 2018 seeed technology co., ltd.
    Author      : Wayen Weng
    Create Time : June 2018
    Change Log  :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef __BOSCH_BMA400_H__
#define __BOSCH_BMA400_H__

#include <Arduino.h>
#include <Wire.h>

#define BMA400_ADDRESS                  0x15

#define BMA400_CHIPID                   0x00
#define BMA400_ERR_REG                  0x02
#define BMA400_STATUS                   0x03

#define BMA400_ACC_X_LSB                0x04
#define BMA400_ACC_X_MSB                0x05
#define BMA400_ACC_Y_LSB                0x06
#define BMA400_ACC_Y_MSB                0x07
#define BMA400_ACC_Z_LSB                0x08
#define BMA400_ACC_Z_MSB                0x09

#define BMA400_SENSOR_TIME_0            0x0A
#define BMA400_SENSOR_TIME_1            0x0B
#define BMA400_SENSOR_TIME_2            0x0C

#define BMA400_EVENT                    0x0D

#define BMA400_INT_STAT0                0x0E
#define BMA400_INT_STAT1                0x0F
#define BMA400_INT_STAT2                0x10

#define BMA400_TEMP_DATA                0x11

#define BMA400_FIFO_LENGTH_0            0x12
#define BMA400_FIFO_LENGTH_1            0x13
#define BMA400_FIFO_DATA                0x14

#define BMA400_STEP_CNT_0               0x15
#define BMA400_STEP_CNT_1               0x16
#define BMA400_STEP_CNT_2               0x17
#define BMA400_STEP_STAT                0x18

#define BMA400_ACC_CONFIG_0             0x19
#define BMA400_ACC_CONFIG_1             0x1A
#define BMA400_ACC_CONFIG_2             0x1B

#define BMA400_INT_CONFIG_0             0x1F
#define BMA400_INT_CONFIG_1             0x20
#define BMA400_INT_1_MAP                0x21
#define BMA400_INT_2_MAP                0x22
#define BMA400_INT_1_2_MAP              0x23
#define BMA400_INT_1_2_CTRL             0x24

#define BMA400_FIFO_CONFIG_0            0x26
#define BMA400_FIFO_CONFIG_1            0x27
#define BMA400_FIFO_CONFIG_2            0x28
#define BMA400_FIFO_PWR_CONFIG          0x29

#define BMA400_AUTO_LOW_POW_0           0x2A
#define BMA400_AUTO_LOW_POW_1           0x2B
#define BMA400_AUTO_WAKE_UP_0           0x2C
#define BMA400_AUTO_WAKE_UP_1           0x2D
#define BMA400_WAKE_UP_INT_CONFIG_0     0x2F
#define BMA400_WAKE_UP_INT_CONFIG_1     0x30
#define BMA400_WAKE_UP_INT_CONFIG_2     0x31
#define BMA400_WAKE_UP_INT_CONFIG_3     0x32
#define BMA400_WAKE_UP_INT_CONFIG_4     0x33

#define BMA400_ORIENTCH_CONFIG_0        0x35
#define BMA400_ORIENTCH_CONFIG_1        0x36
#define BMA400_ORIENTCH_CONFIG_2        0x37
#define BMA400_ORIENTCH_CONFIG_3        0x38
#define BMA400_ORIENTCH_CONFIG_4        0x39
#define BMA400_ORIENTCH_CONFIG_5        0x3A
#define BMA400_ORIENTCH_CONFIG_6        0x3B
#define BMA400_ORIENTCH_CONFIG_7        0x3C
#define BMA400_ORIENTCH_CONFIG_8        0x3D
#define BMA400_ORIENTCH_CONFIG_9        0x3E

#define BMA400_GEN_1_INT_CONFIG_0       0x3F
#define BMA400_GEN_1_INT_CONFIG_1       0x40
#define BMA400_GEN_1_INT_CONFIG_2       0x41
#define BMA400_GEN_1_INT_CONFIG_3       0x42
#define BMA400_GEN_1_INT_CONFIG_3_1     0x43
#define BMA400_GEN_1_INT_CONFIG_4       0x44
#define BMA400_GEN_1_INT_CONFIG_5       0x45
#define BMA400_GEN_1_INT_CONFIG_6       0x46
#define BMA400_GEN_1_INT_CONFIG_7       0x47
#define BMA400_GEN_1_INT_CONFIG_8       0x48
#define BMA400_GEN_1_INT_CONFIG_9       0x49

#define BMA400_GEN_2_INT_CONFIG_0       0x4A
#define BMA400_GEN_2_INT_CONFIG_1       0x4B
#define BMA400_GEN_2_INT_CONFIG_2       0x4C
#define BMA400_GEN_2_INT_CONFIG_3       0x4D
#define BMA400_GEN_2_INT_CONFIG_3_1     0x4E
#define BMA400_GEN_2_INT_CONFIG_4       0x4F
#define BMA400_GEN_2_INT_CONFIG_5       0x50
#define BMA400_GEN_2_INT_CONFIG_6       0x51
#define BMA400_GEN_2_INT_CONFIG_7       0x52
#define BMA400_GEN_2_INT_CONFIG_8       0x53
#define BMA400_GEN_2_INT_CONFIG_9       0x54

#define BMA400_ACT_CH_CONFIG_0          0x55
#define BMA400_ACT_CH_CONFIG_1          0x56

#define BMA400_TAP_CONFIG_0             0x57
#define BMA400_TAP_CONFIG_1             0x58

#define BMA400_STEP_COUNTER_CONFIG_0    0x59
#define BMA400_STEP_COUNTER_CONFIG_1    0x5A
#define BMA400_STEP_COUNTER_CONFIG_2    0x5B
#define BMA400_STEP_COUNTER_CONFIG_3    0x5C
#define BMA400_STEP_COUNTER_CONFIG_4    0x5D
#define BMA400_STEP_COUNTER_CONFIG_5    0x5E
#define BMA400_STEP_COUNTER_CONFIG_6    0x5F
#define BMA400_STEP_COUNTER_CONFIG_7    0x60
#define BMA400_STEP_COUNTER_CONFIG_8    0x61
#define BMA400_STEP_COUNTER_CONFIG_9    0x62
#define BMA400_STEP_COUNTER_CONFIG_10   0x63
#define BMA400_STEP_COUNTER_CONFIG_11   0x64
#define BMA400_STEP_COUNTER_CONFIG_12   0x65
#define BMA400_STEP_COUNTER_CONFIG_13   0x66
#define BMA400_STEP_COUNTER_CONFIG_14   0x67
#define BMA400_STEP_COUNTER_CONFIG_15   0x68
#define BMA400_STEP_COUNTER_CONFIG_16   0x69
#define BMA400_STEP_COUNTER_CONFIG_17   0x6A
#define BMA400_STEP_COUNTER_CONFIG_18   0x6B
#define BMA400_STEP_COUNTER_CONFIG_19   0x6C
#define BMA400_STEP_COUNTER_CONFIG_20   0x6D
#define BMA400_STEP_COUNTER_CONFIG_21   0x6E
#define BMA400_STEP_COUNTER_CONFIG_22   0x6F
#define BMA400_STEP_COUNTER_CONFIG_23   0x70
#define BMA400_STEP_COUNTER_CONFIG_24   0x71

#define BMA400_IF_CONF                  0x7C
#define BMA400_SELF_TEST                0x7D
#define BMA400_CMD                      0x7E

enum power_type_t { // power mode
    SLEEP = 0x00, // Stop conversion, the lowest power mode
    LOW_POWER = 0x01, //
    NORMAL = 0x02, //
};

enum scale_type_t { // measurement rage
    RANGE_2G = 0x00, //
    RANGE_4G = 0x01, //
    RANGE_8G = 0x02, //
    RANGE_16G = 0x03, //
};

enum odr_type_t { // output data rate
    ODR_12 = 0x00, //
    ODR_25 = 0x06, //
    ODR_50 = 0x07, //
    ODR_100 = 0x08, //
    ODR_200 = 0x09, //
    ODR_400 = 0x0A, //
    ODR_800 = 0x0B, //
};

class BMA400 {
  public:

    BMA400(void);

    bool isConnection(void);

    void initialize(void);

    void setPoweMode(power_type_t mode);
    void setFullScaleRange(scale_type_t range);
    void setOutputDataRate(odr_type_t odr);

    void getAcceleration(float* x, float* y, float* z);
    float getAccelerationX(void);
    float getAccelerationY(void);
    float getAccelerationZ(void);

    int16_t getTemperature(void);

    uint8_t getDeviceID(void);

    void reset(void);

  private:

    void write8(uint8_t reg, uint8_t val);
    uint8_t read8(uint8_t reg);
    uint16_t read16(uint8_t reg);
    uint32_t read24(uint8_t reg);
    void read(uint8_t reg, uint8_t* buf, uint16_t len);

    float accRange;
    uint8_t devAddr;

};

extern BMA400 bma400;

#endif
