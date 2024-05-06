# Single Slave Device Aggregation Example {#dmm_exm_ssdA}

Example to demonstrate usage of this library to create and manage a single device in a serial environment.
This example can be configured via `idf.py menuconfig`, additional information can be found below.

## Usage

This example is best used with either a PC-Based Modbus Slave Emulator (A potential application can be found
[here](https://www.modbustools.com/modbus_slave.html)) or a physical device that offers similar functionality.

When this example works correctly it should:
1. Read Registers 1,2, and 4 for Slave 1
2. Print their contents to the console
3. Increment their values by 1
4. Write them to their origin Registers.
5. Wait 1000ms and Repeat

Registers 1, 2 and 4 are interpreted as `uint16_t`, `uint32_t` and `float` respectively.

## Compatible Devices

This example has been tested successfully with:
- ESP32S3

## Configuration

| Element                   | Description                                                 |
|---------------------------|-------------------------------------------------------------|
| UART Port Number          | The number of the UART-Port to be used                      |
| Modbus Baudrate           | The speed of the Modbus Communication in Baud               |
| UART RXD Pin number       | The pin number of the Receive Pin                           |
| UART TXD Pin number       | The pin number of the Transmit Pin                          |
| UART RTS Pin number       | The pin number of the RTS Pin                               |
| Modbus Communication Mode | *Currently not implemented* Switch between Modbus RTU/Ascii |
