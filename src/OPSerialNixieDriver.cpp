#include "OPSerialNixieDriver.h"

OPSerialNixieDriver::OPSerialNixieDriver(int numberOfDigits) {
    this->_numberOfDigits = numberOfDigits;
    this->serialData = new uint8_t[_numberOfDigits * 2];

    digits = new OPSerialNixieDigit *[this->_numberOfDigits];
    for (int i = 0; i < _numberOfDigits; i++) {
        digits[i] = new OPSerialNixieDigit();
    }
}

int OPSerialNixieDriver::getDigitValue(int number, int digit) {
    int positionDivider = pow(10, digit);
    return (number / positionDivider) % 10;
}

void OPSerialNixieDriver::setValue(int value) {
    _value = value;
}

void OPSerialNixieDriver::setEnabled(bool enabled) {
    _enabled = enabled;
}

void OPSerialNixieDriver::render() {
//    this->serialData = new uint8_t[_numberOfDigits * 2];
    for (int i = 0; i < _numberOfDigits; i++) {
        digits[i]->setEnabled(_enabled);
        digits[i]->setDigitValue(getDigitValue(this->_value, i));
        digits[i]->calculate(serialData + (2 * i));
    }

    digitalWrite(_latchPin, LOW);
    for (int i = 0; i < (_numberOfDigits); i++) {
        shiftOut(_dataPin, _clockPin, _bitOrder, serialData[(i * 2) + 1]);
        shiftOut(_dataPin, _clockPin, _bitOrder, serialData[i * 2]);
//        printBinary(serialData[i * 2]);
//        Serial.print('\t');
//        printBinary(serialData[(i * 2) + 1]);
//        Serial.print('\t');
//    }
    }
    digitalWrite(_latchPin, HIGH);
//    Serial.println();
}

void OPSerialNixieDriver::setShiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin) {
    _dataPin = dataPin;
    _latchPin = latchPin;
    _clockPin = clockPin;
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);
}

void OPSerialNixieDriver::setBitOrder(uint8_t bitOrder) {
    _bitOrder = bitOrder;
}

//void OPSerialNixieDriver::printBinary(uint8_t byte) {
//    for (int b = 7; b >= 0; b--)
//        Serial.print(bitRead(byte, b));
//}
