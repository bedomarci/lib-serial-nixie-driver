//
// Created by bedom on 1/18/2021.
//

#ifndef OPNIXIEDRIVER_H
#define OPNIXIEDRIVER_H

#include <stdint.h>
#include <Arduino.h>
#include "OPSerialNixieDigit.h"


class OPSerialNixieDriver {
public:
    OPSerialNixieDriver(int numberOfDigits);

    void setValue(int value);

    void setEnabled(bool enabled);

    void setShiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);

    void setBitOrder(uint8_t bitOrder);

//    void printBinary(uint8_t byte);
    void render();

protected:
    uint8_t _clockPin, _dataPin, _latchPin;
    uint8_t _bitOrder = MSBFIRST;
    uint8_t *serialData;
    OPSerialNixieDigit **digits = nullptr;
    int _numberOfDigits = 1;
    int _value = 0;
    int _enabled = false;

    int getDigitValue(int number, int digit);

private:

};


#endif //OPNIXIEDRIVER_H
