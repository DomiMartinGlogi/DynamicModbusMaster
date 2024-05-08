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
#include <SlaveDeviceIfc.h>

namespace dynamic_modbus_master::slave {
/**
 * @brief A class representing a slave device in a Modbus network.
 *
 * @details Tested Example Implementation of dynamic_modbus_master::slave::SlaveDeviceIfc,
 * can be used as-is and will be most supported. However this can also serve as a template
 * for a potential custom implementation.
 *
 * @details Provides a standardised object to write to and read from a SlaveDevice, whether
 * via Aggregation or via Inheritance.
 */
class SlaveDevice: public SlaveDeviceIfc<SlaveDevice>{
public:
    /**
     * @brief A class representing a slave device in a Modbus network.
     *
     * @details This class provides functionality to initialize and communicate with a slave device using the Modbus protocol.
     */
    SlaveDevice(uint8_t address, uint8_t retries);
    
    ~SlaveDevice() override = default;
    
    /**
     * @brief Writes data to the holding registers of a Modbus slave device.
     *
     * @details This function sends a Modbus request to write data to the holding registers of a specified register address in a slave device.
     * The function takes the register address and the data to write as parameters and returns a `ModbusError` object indicating the status of the write request.
     *
     * @details This method determines what Modbus Function to use at compile time, based on the type of the Data provided.
     * If Type T can be represented in a single Holding register, it will use Function Code 0x06, if it can be represented
     * in a Natural Number of Holding Registers larger than 1 it will use Function Code 0x10. If it cannot be represented
     * in a Natural Number of Holding Registers compilation will fail. See dynamic_modbus_master::ModbusData
     *
     * @tparam T The type of data to be written to the holding registers. This type must meet the `ModbusData` concept requirements.
     * @param reg The register address to start writing to.
     * @param data The data to write to the holding registers.
     * @return A `ModbusError` object indicating the status of the write request.
     */
    template<ModbusData T>
    ModbusError writeHolding(uint16_t reg, T data) const {
        mb_param_request_t request {
                .slave_addr = m_address,
            .command = 0x06,
            .reg_start = reg,
            .reg_size = (std::is_same_v<bool, T>? 1 : sizeof(T) / 2)
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
        mb_param_request_t request {
                .slave_addr = m_address,
                .command = 0x03,
                .reg_start = reg,
                .reg_size = sizeof(T) / sizeof(uint16_t)
        };
        
        T data = 0;
        ModbusError error = sendRequest(request, &data);
        
        return SlaveReturn{error, data};
    }
    
    
    /**
     * @brief Writes data to the coils of a Modbus slave device.
     *
     * @details This function sends a Modbus request to write data to the coils of a specified register address in a slave device.
     * The function takes the register address, the data to write, and the number of coils to write as parameters and returns a `ModbusError` object indicating the status of the write request.
     *
     * @details If the data type `T` is `bool` and the number of coils is 1, this function uses Modbus function code 0x05.
     * If the data type `T` is not `bool` and the number of coils is greater than 1, this function uses Modbus function code 0x0F.
     * Otherwise, an `INVALID_ARG` error is returned.
     *
     * @tparam T The type of data to be written to the coils. This type must meet the `ModbusData` concept requirements.
     * @param reg The register address to start writing to.
     * @param data The data to write to the coils.
     * @param coilNum The number of coils to write.
     * @return A `ModbusError` object indicating the status of the write request.
     */
    template<ModbusData T>
    ModbusError writeCoils(uint16_t reg, const T data, uint16_t coilNum) const {
        if (std::is_same_v<T, bool> && coilNum == 1) {
            mb_param_request_t request {
                .slave_addr = m_address,
                .command = 0x05,
                .reg_start = reg,
                .reg_size = coilNum
            };
            
            uint16_t sendData = (data == true ? 0xFF00 : 0x0000);
            
            return sendRequest(request, &sendData);
        } else if (!(std::is_same_v<T, bool>) && (coilNum > 1)){
            T sendData = data;
            mb_param_request_t  request {
                .slave_addr = m_address,
                .command = 0x0F,
                .reg_start = reg,
                .reg_size = coilNum
            };
            
            return sendRequest(request, &sendData);
        } else {
            return ModbusError::INVALID_ARG;
        }
    }
    
    /**
        * @brief Reads data from the coils of a Modbus slave device.
        *
        * @details This function sends a Modbus request to read data from the coils of a
        * specified register address in a slave device. The function takes the register address
        * and the number of coils to read as parameters and returns a `SlaveReturn`
        * object containing the read data and any error that occurred.
        *
        * @tparam T The type of data to be read from the coils. This type must meet the `ModbusData` concept requirements.
        * @param reg The register address to start reading from.
        * @param coilNum The number of coils to read.
        * @return A `SlaveReturn` object containing the read data and the status of the read request.
        */
    template<ModbusData T>
    SlaveReturn<T> readCoils(uint16_t reg, uint16_t coilNum) {
        mb_param_request_t request {
            .slave_addr = m_address,
            .command = 0x01,
            .reg_start = reg,
            .reg_size = coilNum
        };
        if (std::is_same_v<T, bool> && coilNum == 1) {
            uint8_t data = 0;
            ModbusError error = sendRequest(request, &data);
            return {error, (data != 0)};
        } else if (!(std::is_same_v<T, bool> && coilNum > 1)) {
            T data;
            ModbusError error = sendRequest(request, &data);
            return {error, data};
        } else {
            return {ModbusError::INVALID_ARG, 0};
        }
    }
    
    /**
     * @brief Reads data from the input registers of a Modbus slave device.
     *
     * @details This function sends a Modbus request to read data from the input registers of a specified register address in a slave device.
     * The function takes the register address as a parameter and returns a `SlaveReturn` object containing the read data and any error that occurred.
     *
     * @tparam T The type of data to be read from the input registers. This type must meet the `ModbusData` concept requirements.
     * @param reg The register address to start reading from.
     * @return A `SlaveReturn` object containing the read data and the status of the read request.
     */
    template<ModbusData T>
    SlaveReturn<T> readInputs(uint16_t reg) {
        mb_param_request_t request {
            .slave_addr = m_address,
            .command = 0x04,
            .reg_start = reg,
            .reg_size = (std::is_same_v<bool, T>? 1 : sizeof(T) / 2)
        };
        
        T data = 0;
        ModbusError error;
        error = sendRequest(request, &data);
        
        return {error, data};
    }
    
    /**
     * @brief Reads data from the discrete inputs of a Modbus slave device.
     *
     * @tparam T The type of data to be read from the discrete inputs. This type must meet the `ModbusData` concept requirements.
     * @param reg The register address to start reading from.
     * @return A `SlaveReturn` object containing the read data and the status of the read request.
     */
    template<ModbusData T>
    SlaveReturn<T> readDiscreteInputs(uint16_t reg) {
        mb_param_request_t request {
                .slave_addr = m_address,
                .command = 0x02,
                .reg_start = reg,
                .reg_size = (std::is_same_v<bool, T>? 1 : sizeof(T) * 8)
        };
        
        if (std::is_same_v<bool, T>) {
            uint8_t data = 0;
            ModbusError error;
            error = sendRequest(request, &data);
            
            return {error, (data != 0)};
        } else {
            T data = 0;
            ModbusError error;
            error = sendRequest(request, &data);
            
            return {error, data};
        }
    }
    
private:
    uint8_t m_address;
    uint8_t m_retries;
    
    /**
     * @brief Helper function to send a modbus request
     *
     * @brief This function handles all requests in a consistent manner and if a timeout occurs, re-attempts the request
     * for the specified amount of time.
     *
     * @param request Struct containing the request
     * @param data void* pointing at the target data, in case of reading requests, the data will be written to here,
     * in case of writing requests, the data will be read from here.
     * @return ModbusError containing either the error. <br>
     * Possible Error Codes:
     * <ul>
     * <li> ModbusError::OK - Indicating the request was successful.
     * <li> ModbusError::TIMEOUT - Indicating a timeout occurred.
     * <li> ModbusError::INVALID_ARG - Indicating an Argument was invalid.
     * <li> ModbusError::INVALID_RESPONSE - Indicating that the receiving device returned an invalid response.
     * <li> ModbusError::SLAVE_NOT_SUPPORTED - Indicating that the receiving device doesn't support the command specified in the request.
     * <li> ModbusError::FAILURE_OR_EXCEPTION - Indicating that a generic failure or exception occurred.
     * </ul>
     */
    ModbusError sendRequest(mb_param_request_t request, void* data) const;
};
}
#endif //DYNAMIC_MODBUS_MASTER_SLAVEDEVICE_H
