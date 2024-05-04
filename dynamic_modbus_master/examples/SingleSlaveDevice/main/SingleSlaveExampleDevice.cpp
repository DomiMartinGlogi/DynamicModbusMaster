//Copyright (c) 2024 Dominik M. Glogowski
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include "SingleSlaveExampleDevice.h"

SingleSlaveExampleDevice::SingleSlaveExampleDevice(uint8_t address, uint8_t retries) : SlaveDevice(address, retries){

}

uint16_t SingleSlaveExampleDevice::readExampleSingleRegister() {
    dynamic_modbus_master::slave::SlaveReturn<uint16_t> slaveReturn = readHolding<uint16_t>(1);
    if (slaveReturn.error == dynamic_modbus_master::ModbusError::OK) {
        return slaveReturn.data;
    } else {
        return -1;
    }
}

uint32_t SingleSlaveExampleDevice::readExampleMultipleRegisters() {
    dynamic_modbus_master::slave::SlaveReturn<uint32_t> slaveReturn = readHolding<uint32_t>(2);
    if (slaveReturn.error == dynamic_modbus_master::ModbusError::OK) {
        return slaveReturn.data;
    } else {
        return -1;
    }
}

float SingleSlaveExampleDevice::readExampleFloat() {
    dynamic_modbus_master::slave::SlaveReturn<float> slaveReturn = readHolding<float>(4);
    if (slaveReturn.error == dynamic_modbus_master::ModbusError::OK) {
        return slaveReturn.data;
    } else {
        return -1;
    }
}

void SingleSlaveExampleDevice::writeExampleSingleRegister(uint16_t data) {
    writeHolding(1, data);
}

void SingleSlaveExampleDevice::writeExampleMultipleRegisters(uint32_t data) {
    writeHolding(2, data);
}

void SingleSlaveExampleDevice::writeExampleFloat(float data) {
    writeHolding(4, data);
}
