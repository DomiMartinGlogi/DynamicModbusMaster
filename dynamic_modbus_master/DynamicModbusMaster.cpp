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

consteval mb_communication_info_t defaultCommInfo() {
    return {
            .mode = MB_MODE_RTU,
            .slave_addr = 0,
            .parity = UART_PARITY_DISABLE,
            .dummy_port = 0
    };
}

ModbusError DynamicModbusMaster::initialise(ModbusConfig config) {
    m_config = config;
    esp_err_t error = mbc_master_init(MB_PORT_SERIAL_MASTER, &m_handle);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occured while trying to initialise the port %s", esp_err_to_name(error));
        if (error == ESP_ERR_NOT_SUPPORTED) {
            return ModbusError::PORT_NOT_SUPPORTED;
        } else if (error == ESP_ERR_INVALID_STATE) {
            return ModbusError::INVALID_STATE;
        } else {
            return ModbusError::FAILURE_OR_EXCEPTION;
        }
    }
    
    mb_communication_info_t commInfo = defaultCommInfo();
    
    commInfo.port = m_config.uartPort;
    commInfo.baudrate = m_config.baudRate;
    
    error = mbc_master_setup(&commInfo);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occurred while trying to set up the communication parameters: %s",
                 esp_err_to_name(error));
        return ModbusError::INVALID_ARG;
    }
    
    error = uart_set_pin(m_config.uartPort, m_config.txdPin, m_config.rxdPin, m_config.rtsPin, UART_PIN_NO_CHANGE);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occurred while setting the UART pins: %s", esp_err_to_name(error));
        return ModbusError::FAILURE_OR_EXCEPTION;
    }
    
    error = uart_set_mode(m_config.uartPort, UART_MODE_RS485_HALF_DUPLEX);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occured while setting the UART mode %s", esp_err_to_name(error));
        return ModbusError::INVALID_ARG;
    }
    
    return ModbusError::OK;
}

ModbusError DynamicModbusMaster::start() {
    esp_err_t error = mbc_master_start();
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occurred while starting the Modbus communication stack: %s", esp_err_to_name(error));
        return ModbusError::INVALID_ARG;
    }
    return ModbusError::OK;
}

ModbusError DynamicModbusMaster::stop() {
    esp_err_t error = mbc_master_destroy();
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "An error occured while trying to stop and destroy the modbus communication stack %s",
                 esp_err_to_name(error));
        return ModbusError::INVALID_STATE;
    }
    return ModbusError::OK;
}
}
