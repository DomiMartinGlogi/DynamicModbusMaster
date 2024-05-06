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
 * @tparam T The derived class that implements the interface
 */
template<class T>
class SlaveDeviceIfc {
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
};
}

#endif //DYNAMIC_MODBUS_MASTER_SLAVEDEVICEIFC_H
