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

#ifndef DYNAMIC_MODBUS_MASTER_MODBUSERROR_H
#define DYNAMIC_MODBUS_MASTER_MODBUSERROR_H

#include <cinttypes>

namespace dynamic_modbus_master {
/**
 * @brief Modbus Error Type Enum
 */
enum class ModbusError : uint8_t {
    OK = 0,                     //!< Indicates no error has occured
    INVALID_ARG = 1,            //!< A given Argument was invalid
    INVALID_RESPONSE = 2,       //!< The Slave Device Response was invalid
    ADDRESS_UNAVAILABLE = 3,    //!< This slave address is not available
    SLAVE_NOT_SUPPORTED = 4,    //!< The slave does not support this function
    PORT_NOT_SUPPORTED = 5,     //!< This Port is not supported
    INVALID_STATE = 6,          //!< The Modbus Driver or the Device is in an invalid state
    TIMEOUT = 7,                //!< The Driver experienced a timeout
    FAILURE = 8,                //!< The slave device experienced an undetermined failure.
    // General Exception Codes
    ILLEGAL_FUNCTION = 11,      //!< The received Function code is not available on the target device
    ILLEGAL_DATA_ADDRESS = 12,  //!< The Data Address received is not available
    ILLEGAL_DATA_VALUE = 13,    //!< The Data Value received is of an invalid length
    SLAVE_DEVICE_FAILURE = 14,  //!< An Unrecoverable Error occured while trying to perform the request
    ACKNOWLEDGE = 15,           //!< The Target accepted the Request but will take some time to complete it, this is returned to prevent a Timeout for complex requests
    SLAVE_DEVICE_BUSY = 16,     //!< The Target is currently busy executing a command, retransmit the command at a later time
    MEMORY_PARITY_ERROR = 18,   //!< The Extended File Area failed to pass a consistency check

    //
    GATEWAY_PATH_UNAVAILABLE = 20,      //!< No Path was found between the Input and the Output Port of the Gateway, gateway is possibly misconfigured or overloaded
    GATEWAY_TARGET_NO_RESPONSE = 21,    //!< Gateway Target Device did not respond or does not exist.
};
}

#endif //DYNAMIC_MODBUS_MASTER_MODBUSERROR_H
