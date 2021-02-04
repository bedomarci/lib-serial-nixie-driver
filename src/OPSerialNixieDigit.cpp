//
// Created by bedom on 1/18/2021.
//

#include "OPSerialNixieDigit.h"


void OPSerialNixieDigit::calculate(uint8_t *dataArray) {
    uint16_t data = 0;
    if (_enabled)
        bitSet(data, this->_value);

    (this->_enabled) ? bitSet(data, BIT_ENABLE) : bitClear(data, BIT_ENABLE);

    dataArray[0] = lowByte(data);
    dataArray[1] = highByte(data);
}

void OPSerialNixieDigit::setDigitValue(int value) {
    _value = value;
}

void OPSerialNixieDigit::setEnabled(int enabled) {
    _enabled = enabled;
}

int OPSerialNixieDigit::getValue() {
    return _value;
}
