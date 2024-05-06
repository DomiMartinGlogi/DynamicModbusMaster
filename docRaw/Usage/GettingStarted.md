# Getting Started {#dmm_getStart}

## Requirements

- esp-modbus
- ESP-IDF Version 5.0, preferably higher

You can include this library by using `idf.py domimartinglogi/dynamic_modbus_master`.

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

To access a register, the implemented `MyDevice` can simply call the appropriate method (see `dynamic_modbus_master::slave::SlaveDevice`).

For further info see [here](@ref )

## Stopping

To stop and deinitialise the modbus, simply call the `stop` Method on the `dynamic_modbus_master::DynamicModbusMaster` object.

@warning This is not just stopping the bus, but also removing it from memory and will prevent any further usages of the bus until the bus is reinitialised.

