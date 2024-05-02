# Dynamic Modbus Master Requirements

## Modbus Master

1. Users should be able to configure Modbus within the menuconfig
   - It is unlikely that a user should wish to change the buses definition regarding baud rate 
   - It is even more unlikely that the buses pin definitions might change
2. Users should be able to initialise and start the Modbus with minimal effort
3. Users should be able to stop and deinitalise the Modbus

## Modbus Slave Device

1. Users should be able to create and delete devices on the fly
2. Users should be able to safely send and receive data from a device
3. Users should be able to easily manage a variable amount of devices
4. Users should be able to easily create their own device types
5. Data being sent and received should be type safe -> Only Modbus Compatible Types
