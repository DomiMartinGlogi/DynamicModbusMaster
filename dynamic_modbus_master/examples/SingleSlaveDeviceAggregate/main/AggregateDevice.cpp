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

#include "AggregateDevice.h"
#include <ModbusErrorHelper.h>

AggregateDevice::AggregateDevice(uint8_t address, uint8_t retries, const dynamic_modbus_master::DynamicModbusMaster & master):
        m_device(address, retries, master) {
}

uint16_t AggregateDevice::readExampleSingleRegister() {
    dynamic_modbus_master::slave::SlaveReturn<uint16_t> slaveReturn = m_device.readHolding<uint16_t>(1);
    if (slaveReturn.error == dynamic_modbus_master::ModbusError::OK) {
        return slaveReturn.data;
    } else {
        ESP_LOGE("Single Slave Example Device", "Error Occured : %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(slaveReturn.error).c_str());
        return -1;
    }
}

uint32_t AggregateDevice::readExampleMultipleRegisters() {
    dynamic_modbus_master::slave::SlaveReturn<uint32_t> slaveReturn = m_device.readHolding<uint32_t>(2);
    if (slaveReturn.error == dynamic_modbus_master::ModbusError::OK) {
        return slaveReturn.data;
    } else {
        ESP_LOGE("Single Slave Example Device", "Error Occured : %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(slaveReturn.error).c_str());
        return -1;
    }
}

float AggregateDevice::readExampleFloat() {
    dynamic_modbus_master::slave::SlaveReturn<float> slaveReturn = m_device.readHolding<float>(4);
    if (slaveReturn.error == dynamic_modbus_master::ModbusError::OK) {
        return slaveReturn.data;
    } else {
        ESP_LOGE("Single Slave Example Device", "Error Occured : %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(slaveReturn.error).c_str());
        return -1;
    }
}

void AggregateDevice::writeExampleSingleRegister(uint16_t data) {
    dynamic_modbus_master::ModbusError error = m_device.writeHolding(1, data);
    if (error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to write Data %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(error).c_str());
    }
}

void AggregateDevice::writeExampleMultipleRegisters(uint32_t data) {
    dynamic_modbus_master::ModbusError error = m_device.writeHolding(2, data);
    if (error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to write Data %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(error).c_str());
    }
}

void AggregateDevice::writeExampleFloat(float data) {
    dynamic_modbus_master::ModbusError error = m_device.writeHolding(4, data);
    if (error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to write Data %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(error).c_str());
    }
}

bool AggregateDevice::readExampleSingleCoil() {
    dynamic_modbus_master::slave::SlaveReturn<bool> slaveReturn = m_device.readCoils<bool>(0, 1);
    if (slaveReturn.error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to read Coil %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(slaveReturn.error).c_str());
    }
    return slaveReturn.data;
}

void AggregateDevice::writeExampleSingleCoil(bool state) {
    dynamic_modbus_master::ModbusError error = m_device.writeCoils(0, state, 1);
    if (error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to write Coil %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(error).c_str());
    }
}

uint16_t AggregateDevice::readExampleMultipleCoils() {
    dynamic_modbus_master::slave::SlaveReturn<uint16_t> slaveReturn = m_device.readCoils<uint16_t>(1, 16);
    if (slaveReturn.error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to read Coils %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(slaveReturn.error).c_str());
    }
    return slaveReturn.data;
}

void AggregateDevice::writeExampleMultipleCoils(uint16_t coilStates) {
    dynamic_modbus_master::ModbusError error = m_device.writeCoils(1, coilStates, 16);
    if (error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to write Coil %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(error).c_str());
    }
}

bool AggregateDevice::readDiscreteInput() {
    dynamic_modbus_master::slave::SlaveReturn<bool> slaveReturn = m_device.readDiscreteInputs<bool>(0);
    if (slaveReturn.error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to read Discrete Input %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(slaveReturn.error).c_str());
    }
    return slaveReturn.data;
}

uint16_t AggregateDevice::readInput() {
    dynamic_modbus_master::slave::SlaveReturn<uint16_t> slaveReturn = m_device.readInputs<uint16_t>(0);
    if (slaveReturn.error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("SingleSlaveExampleDevice", "Failed to read Input %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(slaveReturn.error).c_str());
        return -1;
    }
    return slaveReturn.data;
}
