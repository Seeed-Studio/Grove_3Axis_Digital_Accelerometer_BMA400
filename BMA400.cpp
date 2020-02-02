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

#include "BMA400.h"

BMA400::BMA400(void) {
    devAddr = BMA400_ADDRESS;
}

void BMA400::initialize(void) {
    setPoweMode(NORMAL);
    setFullScaleRange(RANGE_4G);
    setOutputDataRate(ODR_200);
}

bool BMA400::isConnection(void) {
    return (getDeviceID() == 0x90);
}

uint8_t BMA400::getDeviceID(void) {
    return read8(BMA400_CHIPID);
}

void BMA400::reset(void) {
    write8(BMA400_CMD, 0xb6);
}

void BMA400::setPoweMode(power_type_t mode) {
    uint8_t data = 0;

    data = read8(BMA400_ACC_CONFIG_0);
    data = (data & 0xfc) | mode;
    write8(BMA400_ACC_CONFIG_0, data);
}

void BMA400::setFullScaleRange(scale_type_t range) {
    uint8_t data = 0;

    if (range == RANGE_2G) {
        accRange = 2000;
    } else if (range == RANGE_4G) {
        accRange = 4000;
    } else if (range == RANGE_8G) {
        accRange = 8000;
    } else if (range == RANGE_16G) {
        accRange = 16000;
    }

    data = read8(BMA400_ACC_CONFIG_1);
    data = (data & 0x3f) | (range << 6);
    write8(BMA400_ACC_CONFIG_1, data);
}

void BMA400::setOutputDataRate(odr_type_t odr) {
    uint8_t data = 0;

    data = read8(BMA400_ACC_CONFIG_1);
    data = (data & 0xf0) | odr;
    write8(BMA400_ACC_CONFIG_1, data);
}

void BMA400::getAcceleration(float* x, float* y, float* z) {
    uint8_t buf[6] = {0};
    uint16_t ax = 0, ay = 0, az = 0;
    float value = 0;

    read(BMA400_ACC_X_LSB, buf, 6);

    ax = buf[0] | (buf[1] << 8);
    ay = buf[2] | (buf[3] << 8);
    az = buf[4] | (buf[5] << 8);

    if (ax > 2047) {
        ax = ax - 4096;
    }
    if (ay > 2047) {
        ay = ay - 4096;
    }
    if (az > 2047) {
        az = az - 4096;
    }

    value = (int16_t)ax;
    *x = accRange * value / 2048;

    value = (int16_t)ay;
    *y = accRange * value / 2048;

    value = (int16_t)az;
    *z = accRange * value / 2048;
}

float BMA400::getAccelerationX(void) {
    uint16_t ax = 0;
    float value = 0;

    ax = read16(BMA400_ACC_X_LSB);
    if (ax > 2047) {
        ax = ax - 4096;
    }

    value = (int16_t)ax;
    value = accRange * value / 2048;

    return value;
}

float BMA400::getAccelerationY(void) {
    uint16_t ay = 0;
    float value = 0;

    ay = read16(BMA400_ACC_Y_LSB);
    if (ay > 2047) {
        ay = ay - 4096;
    }

    value = (int16_t)ay;
    value = accRange * value / 2048;

    return value;
}

float BMA400::getAccelerationZ(void) {
    uint16_t az = 0;
    float value = 0;

    az = read16(BMA400_ACC_Z_LSB);
    if (az > 2047) {
        az = az - 4096;
    }

    value = (int16_t)az;
    value = accRange * value / 2048;

    return value;
}

int16_t BMA400::getTemperature(void) {
    int8_t data = 0;
    int16_t temp = 0;

    data = (int8_t)read8(BMA400_TEMP_DATA);
    temp = data / 2 + 23;

    return temp;
}

void BMA400::write8(uint8_t reg, uint8_t val) {
    Wire.beginTransmission(devAddr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

uint8_t BMA400::read8(uint8_t reg) {
    uint8_t data = 0;

    Wire.beginTransmission(devAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom((int16_t)devAddr, 1);
    while (Wire.available()) {
        data = Wire.read();
    }

    return data;
}

uint16_t BMA400::read16(uint8_t reg) {
    uint16_t msb = 0, lsb = 0;

    Wire.beginTransmission(devAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom((int16_t)devAddr, 2);
    while (Wire.available()) {
        lsb = Wire.read();
        msb = Wire.read();
    }

    return (lsb | (msb << 8));
}
uint32_t BMA400::read24(uint8_t reg) {
    uint32_t hsb = 0, msb = 0, lsb = 0;

    Wire.beginTransmission(devAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom((int16_t)devAddr, 3);
    while (Wire.available()) {
        lsb = Wire.read();
        msb = Wire.read();
        hsb = Wire.read();
    }

    return (lsb | (msb << 8) | (hsb << 16));
}

void BMA400::read(uint8_t reg, uint8_t* buf, uint16_t len) {
    Wire.beginTransmission(devAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom((int16_t)devAddr, len);
    while (Wire.available()) {
        for (uint16_t i = 0; i < len; i ++) {
            buf[i] = Wire.read();
        }
    }
}

BMA400 bma400;
