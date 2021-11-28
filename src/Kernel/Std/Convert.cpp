//
// Created by user on 11/28/21.
//

#include "Convert.h"

namespace Convert {
    char integerToStringOutput[128];

    const char *IntegerToString(int value) {
        unsigned char isNegative = 0;

        if (value < 0) {
            isNegative = 1;
            value *= -1;
            integerToStringOutput[0] = '-';
        }

        unsigned char size = 0;
        long long sizeTester = (long long) value;
        while (sizeTester / 10 > 0) {
            sizeTester /= 10;
            size++;
        }

        unsigned char index = 0;
        long long newValue = (long long) value;
        while (newValue / 10 > 0) {
            unsigned char remainder = newValue % 10;
            newValue /= 10;
            integerToStringOutput[isNegative + size - index] = remainder + 48;
            index++;
        }
        unsigned char remainder = newValue % 10;
        integerToStringOutput[isNegative + size - index] = remainder + 48;
        integerToStringOutput[isNegative + size + 1] = 0;
        return integerToStringOutput;
    }

    char floatToStringOutput[128];

    const char *FloatToString(float value, unsigned char decimalPlaces) {
        char *intPtr = (char *) IntegerToString((int) value);
        char *floatPtr = floatToStringOutput;

        if (value < 0) {
            value *= -1;
        }

        while (*intPtr != 0) {
            *floatPtr = *intPtr;
            intPtr++;
            floatPtr++;
        }
        *floatPtr = '.';
        floatPtr++;

        float newValue = value - (int) value;

        for (unsigned char i = 0; i < decimalPlaces; i++) {
            newValue *= 10;
            *floatPtr = (int) newValue + 48;
            newValue -= (int) newValue;
            floatPtr++;
        }

        *floatPtr = 0;

        return floatToStringOutput;
    }
};