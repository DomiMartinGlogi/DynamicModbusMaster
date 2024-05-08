# Getting Started {#dmm_getStart}

## Requirements

- esp-modbus
- ESP-IDF Version 5.0, preferably higher

You can include this library by using `idf.py add-dependency domimartinglogi/dynamic_modbus_master`.

## Setting Up the Modbus

To set up the Modbus the example below can be used:

```c++
// Error detection code has been stripped from this example
dynamic_modbus_master::DynamicModbusMaster master;

dynamic_modbus_master::ModbusConfig config {
        .uartPort = static_cast<uart_port_t>(1),
        .rxdPin = 7,
        .txdPin = 8,
        .rtsPin = 9,
        .baudRate = 9600
};

dynamic_modbus_master::ModbusError error = master.initialise(config);
error = master.start();
```

Errors that occur can be checked in a similar manner to the way the esp-idf can:

```c++
if (error != dynamic_modbus_master::ModbusError::OK) {
    // Handle the error
}
```

## Setting Up the First Device Type

When implementing a new device type there is a semantic difference to make:
- If the device ***is*** a modbus slave device, ie it acting is a modbus slave is integral to its function, 
  then using the inheritance-based approach may be appropriate.
- If the device ***has*** a modbus interface, ie its function is not dependent on acting as a modbus slave,
  so the aggregational approach is preferable.

### Inheritance

When the inheritance-based approach is chosen the device should inherit from `dynamic_modbus_master::slave::SlaveDevice`:

```c++
class MyDevice: public dynamic_modbus_master::slave::SlaveDevice {
    public:
    MyDevice(uint16_t address, uint8_t retries);
    virtual ~MyDevice() = default;
};
```

### Aggregation

If the aggregational approach is chosen then the device should own an instance of `dynamic_modbus_master::slave::SlaveDevice`:

```c++
class MyDevice {
    public:
    MyDevice(uint16_t address, uint8_t retries);
    virtual ~MyDevice() = default;
    
    private:
    dynamic_modbus_master::slave::SlaveDevice m_device;
};
```

### Accessing Registers

To access a register, the implemented `MyDevice` can simply call the appropriate method (see `dynamic_modbus_master::slave::SlaveDevice`):

- **Holding Registers Read/Write:**

  - **`writeHolding ` Method:** This method writes data to the holding registers of the Modbus slave device.
    It can take care of different data sizes and adjusts the Modbus Function Code usage accordingly.
    If the data fits within one register, the function code 0x06 is used. If the data spans across multiple registers,
    the function code 0x10 is used.

  - **`readHolding` Method:** This method reads data from the holding registers of the slave device.
    The reading function, which uses the Modbus function code `0x03`, is designed to extract the full contents of the
    number of registers equivalent to the size of the requested data type.

- **Coils Read/Write:**

  - **`writeCoils` Method:** This method writes data to the coils of the Modbus slave device, corresponding to a specified
    register address. This method uses either Modbus function code 0x05 (for single boolean data) or 0x0F (for
    boolean arrays or non-boolean data spanning across multiple coils).

  - **`readCoils` Method:** This method reads data from the coils of the Modbus slave device. If a single boolean value
    is requested, the function uses Modbus function code 0x01 to read the single bit. If non-boolean or multiple values
    are requested, the function reads the amount of coils corresponding to the desired data size.

- **Inputs Read:**

  - **`readInputs` Method:** This method reads data from the input registers of the Modbus slave device.
    Each call reads the number of registers corresponding to the size of the requested data type.

  - **`readDiscreteInputs` Method:** This method reads data from the discrete inputs (single bits) of the Modbus slave device.
    If single boolean value is requested, it reads a single bit. If non-boolean or multiple values are requested,
    it reads enough bits to satisfy the requested data size.

Each of these functions, which ensures type-safety by employing template methods that use the `ModbusData` concept,
returns a representative status object following the Modbus request. This object contains the status of the request (`ModbusError`)
and read data (in case of read operations).

For further info see [here](@ref dmm_slaves)

## Stopping

To stop and deinitialise the modbus, simply call the `stop` Method on the `dynamic_modbus_master::DynamicModbusMaster` object.

@warning This is not just stopping the bus, but also removing it from memory and will prevent any further usages of the bus until the bus is reinitialised.

