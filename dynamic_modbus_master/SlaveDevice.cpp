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

#include "SlaveDevice.h"

namespace dynamic_modbus_master::slave {

ModbusError SlaveDevice::sendRequest(mb_param_request_t request, void *data) const{
    uint8_t attempts = 0;
    esp_err_t error;
    do {
        attempts++;
        error = mbc_master_send_request(m_master.getContext(), &request, data);
        if (error != ESP_ERR_TIMEOUT) {
            break;
        }
    } while(attempts <= m_retries);
    if ((attempts > m_retries && m_retries > 0) || error == ESP_ERR_TIMEOUT) {
        return ModbusError::TIMEOUT;
    } else {
        switch (error) {
            case ESP_OK:
                return ModbusError::OK;
            case ESP_ERR_INVALID_ARG:
                return ModbusError::INVALID_ARG;
            case ESP_ERR_NOT_SUPPORTED:
                return ModbusError::SLAVE_NOT_SUPPORTED;
            case ESP_ERR_INVALID_RESPONSE:
                return ModbusError::INVALID_RESPONSE;
            default:
                return ModbusError::FAILURE;
        }
    }
}

SlaveDevice::SlaveDevice(uint8_t address, uint8_t retries, const DynamicModbusMaster& master): m_address(address), m_retries(retries), m_master(master) {
}

}
