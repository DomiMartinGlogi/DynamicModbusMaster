cmake_minimum_required(VERSION 3.22)

project(SingleSlaveDevice)
idf_component_register(SRCS "SingleSlaveDevice.c"
                    INCLUDE_DIRS ".")
