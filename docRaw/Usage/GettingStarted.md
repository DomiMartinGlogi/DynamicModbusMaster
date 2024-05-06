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

### Inheritance

### Aggregation