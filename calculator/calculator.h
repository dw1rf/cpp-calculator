#pragma once
#include <QString>
class Calculator {
public:
    void SetLeft(double value) { left_ = value; }
    double Calculate(const QString& operation, double right) const;
private:
    double left_ = 0.0;
};
