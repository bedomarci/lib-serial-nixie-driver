#include "OPSerialNixieDriver.h"

OPSerialNixieDriver::OPSerialNixieDriver(int numberOfDigits) {
    this->_numberOfDigits = numberOfDigits;
    this->serialData = new uint8_t[_numberOfDigits * 2];
    this->digitEnabled = new bool[_numberOfDigits];

    digits = new OPSerialNixieDigit *[this->_numberOfDigits];
    for (int i = 0; i < _numberOfDigits; i++) {
        digits[i] = new OPSerialNixieDigit();
        digitEnabled[i] = true;
    }
}

int OPSerialNixieDriver::getDigitValue(int number, int digit) {
    int positionDivider = pow(10, digit);
    return (number / positionDivider) % 10;
}

void OPSerialNixieDriver::setValue(int value) {
    _value = value;
    for (int i = 0; i < _numberOfDigits; i++) {
        int digitValue = getDigitValue(this->_value, i);
//        if (!_unusedDigitVisibility)
//            setDigitEnabled(i, (value >= pow(10, i)));
        digits[i]->setDigitValue(digitValue);
    }
    calculateDigitEnabled();
}

void OPSerialNixieDriver::setDisplayEnabled(bool enabled) {
    _enabled = enabled;
    this->calculateDigitEnabled();
}

void OPSerialNixieDriver::setDigitEnabled(uint8_t index, bool enabled) {
    digitEnabled[index] = enabled;
    this->calculateDigitEnabled();
}

void OPSerialNixieDriver::render() {
    for (int i = 0; i < _numberOfDigits; i++) {
        digits[i]->calculate(serialData + (2 * i));
    }
    digitalWrite(_latchPin, LOW);
    for (int i = 0; i < (_numberOfDigits); i++) {
        shiftOut(_dataPin, _clockPin, _bitOrder, serialData[(i * 2) + 1]);
        shiftOut(_dataPin, _clockPin, _bitOrder, serialData[i * 2]);
//        printBinary(serialData[i * 2]);
//        Serial.print(' ');
//        printBinary(serialData[(i * 2) + 1]);
//        Serial.print(' ');
//        Serial.print(digits[i]->getValue());
//        Serial.print('\t');
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

void OPSerialNixieDriver::printBinary(uint8_t byte) {
    for (int b = 7; b >= 0; b--)
        Serial.print(bitRead(byte, b));
}

void OPSerialNixieDriver::setUnusedDigitVisibility(bool enabled) {
    _unusedDigitVisibility = enabled;

}

void OPSerialNixieDriver::calculateDigitEnabled() {
    for (int i = 0; i < _numberOfDigits; i++) {
        bool enabled = _enabled && this->digitEnabled[i];
        if (!_unusedDigitVisibility)
            enabled &= (_value >= pow(10, i));
        digits[i]->setEnabled(enabled);
    }
}


