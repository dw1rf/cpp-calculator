#include "calculator.h"
#include <cmath>
double Calculator::Calculate(const QString& operation, double right) const {
    if (operation == "+") return left_ + right;
    if (operation == "−") return left_ - right;
    if (operation == "×") return left_ * right;
    if (operation == "÷") return left_ / right;
    if (operation == "xʸ") return std::pow(left_, right);
    return right;
}
