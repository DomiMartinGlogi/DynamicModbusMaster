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

#include "DynamicModbusMaster.h"
#include "dmm_common.h"
#include <esp_modbus_master.h>
#include <esp_modbus_common.h>

namespace dynamic_modbus_master {

ModbusError DynamicModbusMaster::initialise(ModbusConfig config) {
    m_config = config;   
    mb_communication_info_t commInfo = {};
    commInfo.ser_opts.port  = m_config.uartPort;
    commInfo.ser_opts.mode =  m_config.modbusMode;
    commInfo.ser_opts.baudrate = m_config.baudRate;
    commInfo.ser_opts.parity = MB_PARITY_NONE;
    commInfo.ser_opts.uid = 0;
    
    esp_err_t error = mbc_master_create_serial(&commInfo, &m_context);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occurred while trying to create the serial communication: %s",
                 esp_err_to_name(error));
        if (error == ESP_ERR_NOT_SUPPORTED) {
            return ModbusError::PORT_NOT_SUPPORTED;
        } else if (error == ESP_ERR_INVALID_STATE) {
            return ModbusError::INVALID_STATE;
        } else {
            return ModbusError::FAILURE;
        }
    }
    
    error = uart_set_pin(m_config.uartPort, m_config.txdPin, m_config.rxdPin, m_config.rtsPin, UART_PIN_NO_CHANGE);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occurred while setting the UART pins: %s", esp_err_to_name(error));
        return ModbusError::FAILURE;
    }
    
    return ModbusError::OK;
}

ModbusError DynamicModbusMaster::start() {
    esp_err_t error = mbc_master_start(m_context);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occurred while starting the Modbus communication stack: %s", esp_err_to_name(error));
        return ModbusError::INVALID_ARG;
    }
    
    error = uart_set_mode(m_config.uartPort, UART_MODE_RS485_HALF_DUPLEX);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occured while setting the UART mode %s", esp_err_to_name(error));
        return ModbusError::INVALID_ARG;
    }
    
    return ModbusError::OK;
}

ModbusError DynamicModbusMaster::stop() {
    esp_err_t error = mbc_master_stop(m_context);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occured while trying to stop and destroy the modbus communication stack %s",
                 esp_err_to_name(error));
        return ModbusError::INVALID_STATE;
    }
    return ModbusError::OK;
}

void* DynamicModbusMaster::getContext() const {
    return m_context;
}
}
