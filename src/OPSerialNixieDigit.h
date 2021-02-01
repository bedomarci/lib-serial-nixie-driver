#ifndef OPSERIALNIXIEDIGIT_H
#define OPSERIALNIXIEDIGIT_H
#define BIT_ENABLE 10


#include <stdint.h>
#include <Arduino.h>

class OPSerialNixieDigit {
protected:
    bool _enabled;
    int _value;

public:
    void calculate(uint8_t *dataArray);
    void setDigitValue(int value);
    void setEnabled(int enabled);
};


#endif //OPSERIALNIXIEDIGIT_H
