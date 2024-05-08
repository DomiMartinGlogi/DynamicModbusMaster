# Single Slave Device Aggregation Example {#dmm_exm_ssdA}

Example to demonstrate usage of this library to create and manage a single device in a serial environment.
This example can be configured via `idf.py menuconfig`, additional information can be found below.

## Usage

This example is best used with either a PC-Based Modbus Slave Emulator (A potential application can be found
[here](https://www.modbustools.com/modbus_slave.html)) or a physical device that offers similar functionality.

When this example works correctly it should:
1. Read Holding Registers 1,2/3, and 4/5 for Slave 1
2. Read Coils 0-16 for Slave 1
3. Read Discrete Input 0 for Slave 1
4. Read Input 0 for Slave 1
2. Print their contents to the console
3. Increment their values by 1/flip their values, where applicable
4. Write them to their origin Registers.
5. Wait 1000ms and Repeat

### Registers

| Number            | Interpreted Type |
|:------------------|-----------------:|
| Holding Registers |
| 1                 |       `uint16_t` |
| 2 - 3             |       `uint32_t` |
| 4 - 5             |          `float` |
| Coils             |
| 0                 |           `bool` |
| 1 - 16            |       `uint16_t` |
| Discrete Inputs   |
| 0                 |           `bool` |
| Inputs            |
| 0                 |       `uint16_t` |

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
