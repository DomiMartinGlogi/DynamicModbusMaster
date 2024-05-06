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

#ifndef DYNAMIC_MODBUS_MASTER_DYNAMICMODBUSMASTER_H
#define DYNAMIC_MODBUS_MASTER_DYNAMICMODBUSMASTER_H

#include "ModbusError.h"
#include "ModbusConfiguration.h"

namespace dynamic_modbus_master {
/**
 * @brief Modbus Master Controller
 *
 * @brief Dynamic Modbus Master Class to manage the initialisation, starting and destroying of the underlying
 * esp_modbus library.
 */
class DynamicModbusMaster {
public:
    /**
     * @brief Initialize the Modbus Master controller and set up the communication parameters.
     *
     * @details This function initializes the Modbus Master controller and sets up the communication
     * parameters for the Modbus connection.
     *
     * @param config The configuration of the Modbus connection.
     * @return An instance of ModbusError representing the result of the initialization.
     * <ul> Possible Results:
     * <li> ModbusError::OK - Initalisation was successful
     * <li> ModbusError::PORT_NOT_SUPPORTED - The MB Port Type was not supported
     * <li> ModbusError::INVALID_STATE - Inialisation failure
     * <li> ModbusError::INVALID_ARG - Invalid Argument
     * <li> ModbusError::FAILURE_OR_EXCEPTION - Undetermined Failure
     * </ul>
     */
    ModbusError initialise(ModbusConfig config);
    
    /**
     * @brief Start the Modbus communication stack.
     *
     * @details This function starts the Modbus communication stack by calling the `mbc_master_start()` function.
     * If an error occurs during the start process, an error log is generated using the `ESP_LOGE` macro with the tag
     * "DynamicModbusMaster" and the error name is printed using the `esp_err_to_name()` function. The function returns
     * `ModbusError::INVALID_ARG` to indicate an invalid argument error. If the start process is successful, the
     * function returns `ModbusError::OK`.
     *
     * @return An instance of ModbusError representing the result of the start process.
     * <ul> Possible Results:
     * <li> ModbusError::OK - Start process was successful
     * <li> ModbusError::INVALID_ARG - Invalid argument error
     * </ul>
     */
    ModbusError start();
    
    /**
     * @brief Stop the Modbus communication stack.
     *
     * @details This function stops the Modbus communication stack by calling the `mbc_master_destroy()` function.
     * If an error occurs during the stop process, an error log is generated using the `ESP_LOGE` macro with the tag
     * "DynamicModbusMaster" and the error name is printed using the `esp_err_to_name()` function. The function returns
     * `ModbusError::INVALID_STATE` to indicate an invalid state error. If the stop process is successful, the
     * function returns `ModbusError::OK`.
     *
     * @return An instance of ModbusError representing the result of the stop process.
     * <ul> Possible Results:
     * <li> ModbusError::OK - Stop process was successful
     * <li> ModbusError::INVALID_STATE - Invalid state error, likely indicating that the Modbus was never started
     * </ul>
     */
    ModbusError stop();
    
private:
    ModbusConfig m_config;
    void* m_handle;
};
}

#endif //DYNAMIC_MODBUS_MASTER_DYNAMICMODBUSMASTER_H
