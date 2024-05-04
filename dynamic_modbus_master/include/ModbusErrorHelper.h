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

#ifndef DYNAMIC_MODBUS_MASTER_MODBUSERRORHELPER_H
#define DYNAMIC_MODBUS_MASTER_MODBUSERRORHELPER_H

#include <ModbusError.h>
#include <string>

namespace dynamic_modbus_master{

class ModbusErrorHelper {
public:
/**
 * @brief Converts a ModbusError enum value to its corresponding name.
 * @param error The ModbusError enum value.
 * @return The name of the ModbusError.
 *
 * @details This function takes a ModbusError enum value and returns its corresponding
 * name as a string. The ModbusError enum represents different error types
 * that can occur in Modbus communication.
 */
[[maybe_unused]] constexpr static std::string modbusErrorToName(const ModbusError error) {
        switch (error) {
            case ModbusError::OK:
                return "OK";
                break;
            case ModbusError::INVALID_ARG:
                return "INVALID_ARG";
                break;
            case ModbusError::INVALID_RESPONSE:
                return "INVALID_RESPONSE";
                break;
            case ModbusError::ADDRESS_UNAVAILABLE:
                return "ADDRESS_UNAVAILABLE";
                break;
            case ModbusError::SLAVE_NOT_SUPPORTED:
                return "SLAVE_NOT_SUPPORTED";
                break;
            case ModbusError::PORT_NOT_SUPPORTED:
                return "PORT_NOT_SUPPORTED";
                break;
            case ModbusError::INVALID_STATE:
                return "INVALID_STATE";
                break;
            case ModbusError::TIMEOUT:
                return "TIMEOUT";
                break;
            case ModbusError::FAILURE_OR_EXCEPTION:
                return "FAILURE_OR_EXCEPTION";
                break;
        }
        return "Invalid Error";
    }
};

} // dynamic_modbus_master

#endif //DYNAMIC_MODBUS_MASTER_MODBUSERRORHELPER_H
