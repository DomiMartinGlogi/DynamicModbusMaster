#include <DynamicModbusMaster.h>
#include <ModbusErrorHelper.h>
#include <sdkconfig.h>
#include <esp_log.h>
#include <inttypes.h>
#include "AggregateDevice.h"

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

AggregateDevice g_exampleDevice(1, 1);

extern "C" void app_main(void) {
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
        auto discreteInputValue = g_exampleDevice.readDiscreteInput();
        auto inputValue = g_exampleDevice.readInput();
        
        ESP_LOGI("Example Device", "Single Register Read: %u ; Multiple Register Read: %" PRIu32 " ; Float Register Read: %f", singleRegisterData, multipleRegisterData, floatRegisterData);
        ESP_LOGI("Example Device", "Single Coil Read: %s ; Multiple Coil Read: %u", (singleCoilValue ? "On" : "Off"), multipleCoilValue);
        ESP_LOGI("Example Device", "Discrete Input State: %s ; Input Value: %u", (discreteInputValue ? "On" : "Off"), inputValue);
        
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
