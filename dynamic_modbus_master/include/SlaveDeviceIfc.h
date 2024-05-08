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

#ifndef DYNAMIC_MODBUS_MASTER_SLAVEDEVICEIFC_H
#define DYNAMIC_MODBUS_MASTER_SLAVEDEVICEIFC_H

#include "dmm_common.h"
#include "ModbusData.hpp"
#include "ModbusError.h"

namespace dynamic_modbus_master::slave {

/**
 * @brief Interface class for slave devices in a Modbus network
 *
 * @details This class provides an interface for slave devices in a Modbus network. It uses CRTP to allow
 * the usage of generic templated virtual Methods.
 *
 * This interface can be used when devices require a different Implementation for their communication
 * from dynamic_modbus_master::slave::SlaveDevice which provides a generally good way to access a
 * device.
 *
 * @note for further info on CRTP see <a href="https://en.cppreference.com/w/cpp/language/crtp"> cppreference </a>,
 * <a href="https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern"> Wikipedia </a> or
 * <a href="https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/"> FluentCPP </a>
 *
 * @tparam T The derived class that implements the interface
 */
template<class T>
class SlaveDeviceIfc {
public:
    virtual ~SlaveDeviceIfc() = default;
    
    /**
     * @brief Write data to a holding register
     *
     * @details This method writes the provided data to a holding register at the specified register address.
     * The data must be of a type that can be represented in Modbus registers, i.e., it must be at least
     * 16-bits or the size of a single Modbus register.
     *
     * @param reg The register address to write the data to
     * @param data The data to be written to the register
     * @tparam D The type of data to be written
     * @return A ModbusError value indicating the success or failure of the write operation
     */
    template<ModbusData D>
    ModbusError writeHolding(uint16_t reg, const D& data) const {
        return static_cast<T const*>(this)->template writeHolding<D>(reg, data);
    }
    
    /**
     * @brief Read data from a holding register
     *
     * @details This method reads data from a holding register at the specified register address.
     * The data read must be of a type that can be represented in Modbus registers, i.e., it must be at least
     * 16-bits or the size of a single Modbus register.
     *
     * @param reg The register address to read the data from
     * @tparam D The type of data to be read
     * @return A SlaveReturn structure containing the read data and any errors encountered during the read operation
     */
    template<ModbusData D>
    SlaveReturn<D> readHolding(uint16_t reg) const {
        return static_cast<T const*>(this)->template readHolding<D>(reg);
    }
    
    /**
     * @brief Write data to a group of coils
     *
     * @details This method writes the provided data to a group of coils starting at the specified coil address.
     *
     * @param reg The coil address to start writing data to
     * @param data The data to be written to the coils
     * @param coilNum The number of coils to write data to
     * @tparam D The type of data to be written, must fulfill the ModbusData concept.
     * @return A ModbusError value indicating the success or failure of the write operation
     */
    template<ModbusData D>
    ModbusError writeCoils(uint16_t reg, const D& data, uint16_t coilNum) {
        return static_cast<T const*>(this)->template writeCoils<D>(reg, data, coilNum);
    }
    
    /**
     * @brief Read data from a group of coils
     *
     * @details This method reads data from a group of coils starting at the specified coil address.
     *
     * @param reg The coil address to start reading data from
     * @param coilNum The number of coils to read data from
     * @tparam D The type as which the read Data will be returned, must fulfill the ModbusData concept.
     * @return A SlaveReturn structure containing the read data and any errors encountered during the read operation
     */
    template<ModbusData D>
    SlaveReturn<D> readCoils(uint16_t reg, uint16_t coilNum) {
        return static_cast<T const *>(this)->template readCoils<D>(reg, coilNum);
    }
    
    /**
    * @brief Read data from input registers
    *
    * @details This method reads data from input registers at the specified register address. Input registers are read-only
    * and contain data from the slave device.
    *
    * @param reg The register address to read the data from
    * @tparam D The type of data to be read from input registers, must fulfill the ModbusData concept
    * @return A SlaveReturn structure containing the read data and any errors encountered during the read operation
    */
    template<ModbusData D>
    SlaveReturn<D> readInputs(uint16_t reg) {
        return static_cast<T const *>(this)->template readInputs<D>(reg);
    }
    
    /**
     * @brief Reads data from discrete inputs in a Modbus slave device.
     *
     * @details This function reads data from discrete inputs in a Modbus slave device at the specified register address.
     * The function is templated to allow reading data of different types. The type of data to be read must fulfill the
     * ModbusData concept. The function delegates the actual implementation to the derived class implementing the interface.
     *
     * @tparam D The type of data to be read, must fulfill the ModbusData concept
     * @param reg The register address to read the data from
     * @return A SlaveReturn structure containing the read data and any errors encountered during the read operation
     */
    template<ModbusData D>
    SlaveReturn<D> readDiscreteInputs(uint16_t reg) {
        return static_cast<T const *>(this)->template readDiscreteInputs<D>(reg);
    }
};
}

#endif //DYNAMIC_MODBUS_MASTER_SLAVEDEVICEIFC_H
