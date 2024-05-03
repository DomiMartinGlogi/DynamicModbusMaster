# Dynamic Modbus Master Requirements {#dmm_req}

## Modbus Master

1. Users should be able to configure Modbus within the menuconfig
   - It is unlikely that a user should wish to change the buses definition regarding UART-Port
   - It is even more unlikely that the buses pin definitions might change
2. Users should be able to initialise and start the Modbus with minimal effort
3. Users should be able to stop and deinitalise the Modbus
4. Modbus Serial must be supported.
5. Modbus TCP may be supported in the future.
6. Performance with many devices must be acceptable.

## Modbus Slave Devices

1. Users should be able to create and delete devices on the fly
2. Users should be able to safely send and receive data from a device
3. Users should be able to easily manage a variable amount of devices
4. Users should be able to easily create their own device types
5. Data being sent and received should be type safe -> Only Modbus Compatible Types

## Open Questions

1. Is the call to `mbc_master_send_request` truly blocking?
2. What is performance like with 2+ devices?
3. Modbus TCP integration?
4. Custom type support for Modbus Slaves?
