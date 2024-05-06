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

#ifndef DYNAMIC_MODBUS_MASTER_SLAVEDEVICE_H
#define DYNAMIC_MODBUS_MASTER_SLAVEDEVICE_H
#include "ModbusData.hpp"
#include <ModbusError.h>
#include <esp_modbus_master.h>

namespace dynamic_modbus_master::slave {
class SlaveDevice{
public:
    /**
     * @brief Initializes the SlaveDevice.
     *
     * @details This function initializes the SlaveDevice by performing any necessary setup and configuration.
     * It should be called before any other operations on the SlaveDevice.
     *
     * @return A ModbusError object indicating the status of the initialization.
     */
    virtual ModbusError init() final;
    
protected:
    /**
     * @brief A class representing a slave device in a Modbus network.
     *
     * @details This class provides functionality to initialize and communicate with a slave device using the Modbus protocol.
     */
    SlaveDevice(uint8_t address, uint8_t retries);
    
    /**
     * @brief Writes data to the holding registers of a Modbus slave device.
     *
     * @details This function sends a Modbus request to write data to the holding registers of a specified register address in a slave device.
     * The function takes the register address and the data to write as parameters and returns a `ModbusError` object indicating the status of the write request.
     *
     * @tparam T The type of data to be written to the holding registers. This type must meet the `ModbusData` concept requirements.
     * @param reg The register address to start writing to.
     * @param data The data to write to the holding registers.
     * @return A `ModbusError` object indicating the status of the write request.
     */
    template<ModbusData T>
    ModbusError writeHolding(uint16_t reg, T data) const {
        mb_param_request_t request {
                .slave_addr = address,
            .command = 0x06,
            .reg_start = reg,
            .reg_size = sizeof(T) / sizeof(uint16_t)
        };
        if (request.reg_size > 1) {
            request.command = 0x10;
        }
        return sendRequest(request, &data);
    }
    
    /**
     * @brief Reads data from the holding registers of a Modbus slave device.
     *
     * @details This function sends a Modbus request to read data from the holding registers of a specified register address in a slave device.
     * The function takes the register address as a parameter and returns a `SlaveReturn` object containing the read data and any error that occurred.
     *
     * @tparam T The type of data to be read from the holding registers. This type must meet the `ModbusData` concept requirements.
     * @param reg The register address to start reading from.
     * @return A `SlaveReturn` object containing the read data and the status of the read request.
     */
    template<ModbusData T>
    SlaveReturn<T> readHolding(uint16_t reg) const {
        mb_param_request_t request{
                .slave_addr = address,
                .command = 0x03,
                .reg_start = reg,
                .reg_size = sizeof(T) / sizeof(uint16_t)
        };
        
        T data;
        ModbusError error = sendRequest(request, &data);
        
        return SlaveReturn{error, data};
    }
    
private:
    uint8_t address;
    uint8_t retries;
    
    /**
     * @brief Helper function to send a modbus request
     *
     * @brief This function handles all requests in a consistent manner and if a timeout occurs, re-attempts the request
     * for the specified amount of time.
     *
     * @param request Struct containing the request
     * @param data void* pointing at the target data, in case of reading requests, the data will be written to here,
     * in case of writing requests, the data will be read from here.
     * @return ModbusError containing either the error.
     * <ul> Possible Error Codes:
     * <li> ModbusError::OK - Indicating the request was successful. </li>
     * <li> ModbusError::TIMEOUT - Indicating a timeout occurred. </li>
     * <li> ModbusError::INVALID_ARG - Indicating an Argument was invalid </li>
     * <li> ModbusError::INVALID_RESPONSE - Indicating that the receiving device returned an invalid response. </li>
     * <li> ModbusError::SLAVE_NO_SUPPORTED - Indicating that the receiving device doesn't support the command specified in the request. </li>
     * <li> ModbusError::FAILURE_OR_EXCEPTION - Indicating that a generic failure or exception occurred. </li>
     * </ul>
     */
    ModbusError sendRequest(mb_param_request_t request, void* data) const;
};
}
#endif //DYNAMIC_MODBUS_MASTER_SLAVEDEVICE_H
