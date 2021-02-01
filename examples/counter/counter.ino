#include <stdint.h>
#include <Arduino.h>
#include "OPSerialNixieDriver.h"

#define PIN_DATA D1
#define PIN_CLK D2
#define PIN_LATCH D3

int number = 0;
OPSerialNixieDriver driver = OPSerialNixieDriver(1);

void setup() {
    driver.setEnabled(true);
    driver.setBitOrder(MSBFIRST);
    driver.setShiftOut(PIN_DATA, PIN_CLK, PIN_LATCH);
}

void loop() {
    driver.setValue(number);
    driver.render();
    number++;
    delay(150);
}