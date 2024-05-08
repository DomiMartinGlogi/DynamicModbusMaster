CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

idf_component_register(
        SRCS
        "ModbusErrorHelper.cpp"
        "DynamicModbusMaster.cpp"
        "SlaveDevice.cpp"
        INCLUDE_DIRS
        "include"
)

project(dynamic_modbus_master)
