// Copyright (c) 2024 Dominik M. Glogowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef DYNAMIC_MODBUS_MASTER_MODBUSDATA_HPP
#define DYNAMIC_MODBUS_MASTER_MODBUSDATA_HPP

#include <cinttypes>
#include "ModbusError.h"

namespace dynamic_modbus_master {
/**
 * @brief Concept to check if a given Type T can be represented in modbus registers, constrains T to be
 * at least 16-Bits or the size of a single modbus Register.
 *
 * @tparam T The type to check.
 */
template<typename T>
concept ModbusData = (sizeof(T) % sizeof(uint16_t) == 0) && (sizeof(T) > 0);

namespace slave {

/**
 * @brief Represents the return value from a Modbus slave device.
 *
 * @details Template Struct containing the return value of a slave device, unless error is set as ModbusError::OK, data
 * will not be reliable.
 *
 * @tparam T The type of data returned by the slave device. Constrained to be ModbusData
 * @param error ModbusError representing the return value of the request
 * @param data Returned Data as type T
 */
template<ModbusData T>
struct SlaveReturn {
    ModbusError error;
    T data;
};
}
}
#endif //DYNAMIC_MODBUS_MASTER_MODBUSDATA_HPP
