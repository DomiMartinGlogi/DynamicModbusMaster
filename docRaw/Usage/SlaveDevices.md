# Slave Devices {#dmm_slaves}

Proper Implementation of slave devices is crucial to operating properly

@note All code samples in this file are for the inheritance-based implementation but the general idea works for both approaches.

## Holding Registers

### Reading

Reading a holding register can be done using the `dynamic_modbus_master::slave::SlaveDevice::readHolding()` method.

The simplest implementation can look like this:

```c++
class MyDevice : public dynamic_modbus_master::slave::SlaveDevice{
    public:
    MyDevice(uint16_t address, uint8_t retries): SlaveDevice(address, retries) {}
    virtual ~MyDevice = default;
    
    uint16_t readValue() {
        return readHolding<uint16_t>(1).data;
    }
};
```

However the above implementation doesn't handle errors in an appropriate manner so it can be extended to be:

```c++
class MyDevice : public dynamic_modbus_master::slave::SlaveDevice{
    public:
    MyDevice(uint16_t address, uint8_t retries): SlaveDevice(address, retries) {}
    virtual ~MyDevice = default;
    
    uint16_t readValue() {
       dynamic_modbus_master::SlaveReturn<uint16_t> result = readHolding<uint16_t>(1);
       if (result.error != dynamic_modbus_master::ModbusError::OK) {
           return -1;
       } else {
           return result.data;
       }
    }
};
```

In cases where values are in a different byte order or have a different endian-ness this can also be adjusted here.

```c++
class MyDevice : public dynamic_modbus_master::slave::SlaveDevice{
    public:
    MyDevice(uint16_t address, uint8_t retries): SlaveDevice(address, retries) {}
    virtual ~MyDevice = default;
    
    uint16_t readValue() {
       dynamic_modbus_master::SlaveReturn<uint16_t> result = readHolding<uint16_t>(1);
       if (result.error != dynamic_modbus_master::ModbusError::OK) {
           return -1;
       } 
       
       // Reversing the byte Order
       uint8_t bytes[2];
       bytes[0] = reinterpret_cast<uint8_t*>(&results.data)[1];
       bytes[1] = reinterpret_cast<uint8_t*>(&results.data)[0];
       
       return *reinterpret_cast<uint16_t*>(bytes);
    }
};
```

The above-described mechanism works for all datatypes that can be represented in a natural number of Modbus-Registers.
Therefore, it is also possible to bulk-read a group of registers using a custom datatype:

```c++
class MyDevice : public dynamic_modbus_master::slave::SlaveDevice{
    public:
    MyDevice(uint16_t address, uint8_t retries): SlaveDevice(address, retries) {}
    virtual ~MyDevice = default;
    
    RegisterBlock readValue() {
       dynamic_modbus_master::SlaveReturn<RegisterBlock> result = readHolding<RegisterBlock>(1);
       if (result.error != dynamic_modbus_master::ModbusError::OK) {
           return -1;
       } else {
           return result.data;
       }
    }
    private:
    struct RegisterBlock {
        uint16_t registerA;
        uint16_t registerB;
        // We can even mix and match datatypes
        uint32_t registerC;
        float registerD;
        int64_t registerE;
    };
};
```

The bulk-read mechanism only works as long as the registers that are to be read are all in one block.
Any unused registers must also be read and then discarded *or* the block to be read may be split into different
units:

| Register | Description      | Large Block | Small Blocks |
|----------|------------------|-------------|--------------|
| 0        | Temp hundredths  | X           | X            |
| 1        | Temp Units       | X           | X            |
| 2        | Error Count Low  | X           | X            |
| 3        | Error Count High | X           | X            |
| 4        | Unused           | X           |              |
| 5        | Unused           | X           |              |
| 6        | Voltage Low      | X           | X            |
| 7        | Voltage High     | X           | X            |
| 8        | Current Low      | X           | X            |
| 9        | Current High     | X           | X            |

Even in the relatively simple example device above, splitting the read into two smaller blocks may be beneficial,
since this would spread the read into two and use 8-Bytes instead of 10. Additionally, this would allow
to read the registers only when they are needed.

## Coil Registers

@todo Implement reading/writing of Coil Registers and write documentation

## Input Registers

@todo Implement reading of Input Registers and write documentation

## Advanced Uses

For certain use cases the above API might not be sufficient, it is however possible to achieve similar functionality
by implementing the dynamic_modbus_master::slave::SlaveDeviceIfc Interface. As long as this interface is
implemented into a custom class, usage of Slave Devices should be the same from an application perspective.

For an example on how to implement this interface see dynamic_modbus_master::slave::SlaveDevice.

@warning esp-modbus currently does not support user-defined functions without some major adjustments, if your code requires a user defined function, see [here](https://github.com/espressif/esp-modbus/issues/34)