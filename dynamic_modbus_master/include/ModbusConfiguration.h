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

#ifndef DYNAMIC_MODBUS_MASTER_MODBUSCONFIGURATION_H
#define DYNAMIC_MODBUS_MASTER_MODBUSCONFIGURATION_H

#include <driver/uart.h>

namespace dynamic_modbus_master {

/**
 * @struct ModbusConfig
 * @brief Structure to represent the configuration of a Modbus connection.
 *
 * @param uartPort The UART port number to use for Modbus communication, ranging from UART_NUM_0 to UART_NUM_MAX-1.
 * @param rxdPin The pin number of the receive data (RXD) line.
 * @param txdPin The pin number of the transmit data (TXD) line.
 * @param rtsPin The pin number of the request-to-send (RTS) line.
 * @param baudRate The baud rate to use for the UART communication.
 */
struct ModbusConfig {
    uart_port_t uartPort;
    uint8_t rxdPin;
    uint8_t txdPin;
    uint8_t rtsPin;
    uint32_t baudRate;
    };
}

#endif //DYNAMIC_MODBUS_MASTER_MODBUSCONFIGURATION_H
