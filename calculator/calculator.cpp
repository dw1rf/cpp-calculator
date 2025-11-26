//
#include "calculator.h"

#include <cmath>
#include <iostream>
#include <string>

bool ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }

    return true;
}

bool RunCalculatorCycle() {
    Number currentValue = 0.0;

    if (!ReadNumber(currentValue)) {
        return false;
    }

    Number memoryValue = 0.0;
    bool memoryHasValue = false;

    std::string token;

    while (std::cin >> token) {
        if (token == "q") {
            return true;
        }
        else if (token == "+") {
            Number operand = 0.0;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue += operand;
        }
        else if (token == "-") {
            Number operand = 0.0;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue -= operand;
        }
        else if (token == "*") {
            Number operand = 0.0;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue *= operand;
        }
        else if (token == "/") {
            Number operand = 0.0;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue /= operand;
        }
        else if (token == "**") {
            Number exponent = 0.0;
            if (!ReadNumber(exponent)) {
                return false;
            }
            currentValue = std::pow(currentValue, exponent);
        }
        else if (token == ":") {
            Number newValue = 0.0;
            if (!ReadNumber(newValue)) {
                return false;
            }
            currentValue = newValue;
        }
        else if (token == "=") {
            std::cout << currentValue << std::endl;
        }
        else if (token == "c") {
            currentValue = 0.0;
        }
        else if (token == "s") {
            memoryValue = currentValue;
            memoryHasValue = true;
        }
        else if (token == "l") {
            if (!memoryHasValue) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            currentValue = memoryValue;
        }
        else {
            std::cerr << "Error: Unknown token " << token << std::endl;
            return false;
        }
    }

    // ¬вод закончилс€, но команда q не встретилась Ч считаем ошибкой.
    return false;
}
