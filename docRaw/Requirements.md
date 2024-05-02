# Dynamic Modbus Master Requirements

## Modbus Master

1. Users should be able to configure Modbus within the menuconfig
   - It is unlikely that a user should wish to change the buses definition regarding baud rate or UART-Port
   - It is even more unlikely that the buses pin definitions might change
2. Users should be able to initialise and start the Modbus with minimal effort
3. Users should be able to stop and deinitalise the Modbus

## Modbus Slave Device

1. Users should be able to create and delete devices on the fly
2. Users should be able to safely send and receive data from a device
