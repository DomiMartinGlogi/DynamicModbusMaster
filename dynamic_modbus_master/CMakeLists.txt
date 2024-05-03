CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

idf_component_register(
        SRCS
        "ModbusErrorHelper.cpp"
        "DynamicModbusMaster.cpp"
        "SlaveDevice.cpp"
        INCLUDE_DIRS
        "include"
)

project(dynamic_modbus_master)
