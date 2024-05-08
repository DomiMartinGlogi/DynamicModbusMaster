//Copyright (c) 2024 Dominik M. Glogowski
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include <DynamicModbusMaster.h>
#include <ModbusErrorHelper.h>
#include <sdkconfig.h>
#include <esp_log.h>
#include <inttypes.h>
#include "SingleSlaveExampleDevice.h"

dynamic_modbus_master::DynamicModbusMaster master;

dynamic_modbus_master::ModbusConfig config {
    .uartPort = static_cast<uart_port_t>(CONFIG_MB_UART_PORT_NUM),
    .rxdPin = CONFIG_MB_UART_RXD,
    .txdPin = CONFIG_MB_UART_TXD,
    .rtsPin = CONFIG_MB_UART_RTS,
    .baudRate = CONFIG_MB_UART_BAUD_RATE,
    #ifdef CONFIG_MB_COMM_MODE_RTU
    .modbusMode = MB_MODE_RTU,
    #elif CONFIG_MB_COMM_MODE_ASCII
    .modbusMode = MB_MODE_ASCII
    #endif
};

SingleSlaveExampleDevice g_exampleDevice(1, 1);

extern "C" void app_main() {
    dynamic_modbus_master::ModbusError error = master.initialise(config);
    if (error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("app_main", "Modbus initialization failed: %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(error).c_str());
        return;
    }
    
    error = master.start();
    if (error != dynamic_modbus_master::ModbusError::OK) {
        ESP_LOGE("app_main", "Modbus start failed: %s", dynamic_modbus_master::ModbusErrorHelper::modbusErrorToName(error).c_str());
        return;
    }
    
    while(true) {
        auto singleRegisterData = g_exampleDevice.readExampleSingleRegister();
        auto multipleRegisterData = g_exampleDevice.readExampleMultipleRegisters();
        auto floatRegisterData = g_exampleDevice.readExampleFloat();
        auto singleCoilValue = g_exampleDevice.readExampleSingleCoil();
        auto multipleCoilValue = g_exampleDevice.readExampleMultipleCoils();
        
        ESP_LOGI("Example Device", "Single Register Read: %u ; Multiple Register Read: %" PRIu32 " ; Float Register Read: %f", singleRegisterData, multipleRegisterData, floatRegisterData);
        ESP_LOGI("Example Device", "Single Coil Read: %s ; Multiple Coil Read: %u", (singleCoilValue ? "On" : "Off"), multipleCoilValue);
        
        singleRegisterData++;
        multipleRegisterData++;
        floatRegisterData++;
        singleCoilValue = !singleCoilValue;
        multipleCoilValue++;
        
        g_exampleDevice.writeExampleSingleRegister(singleRegisterData);
        g_exampleDevice.writeExampleMultipleRegisters(multipleRegisterData);
        g_exampleDevice.writeExampleFloat(floatRegisterData);
        g_exampleDevice.writeExampleSingleCoil(singleCoilValue);
        g_exampleDevice.writeExampleMultipleCoils(multipleCoilValue);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
