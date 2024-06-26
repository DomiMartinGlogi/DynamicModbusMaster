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

#ifndef DYNAMIC_MODBUS_MASTER_AGGREGATEDEVICE_H
#define DYNAMIC_MODBUS_MASTER_AGGREGATEDEVICE_H

#include <SlaveDevice.h>

class AggregateDevice{
public:
    AggregateDevice(uint8_t address, uint8_t retries);
    
    uint16_t readExampleSingleRegister();
    
    uint32_t readExampleMultipleRegisters();
    
    float readExampleFloat();
    
    void writeExampleSingleRegister(uint16_t data);
    
    void writeExampleMultipleRegisters(uint32_t data);
    
    void writeExampleFloat(float data);
    
    bool readExampleSingleCoil();
    
    void writeExampleSingleCoil(bool state);
    
    uint16_t readExampleMultipleCoils();
    
    void writeExampleMultipleCoils(uint16_t coilStates);
    
    bool readDiscreteInput();
    
    uint16_t readInput();
    
private:
    dynamic_modbus_master::slave::SlaveDevice m_device;
};


#endif //DYNAMIC_MODBUS_MASTER_AGGREGATEDEVICE_H
