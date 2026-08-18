#pragma once

#include "pow.h"
#include "rational.h"

#include <cmath>
#include <optional>
#include <string>
#include <type_traits>

using Error = std::string;

template <class Number>
class Calculator {
public:
    void Set(Number number) {
        number_ = number;
    }

    Number GetNumber() const {
        return number_;
    }

    std::optional<Error> Add(Number number) {
        number_ += number;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number number) {
        number_ -= number;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number number) {
        number_ *= number;
        return std::nullopt;
    }

    std::optional<Error> Div(Number number) {
        if constexpr (!std::is_floating_point_v<Number>) {
            if (number == Number{}) {
                return Error("Division by zero");
            }
        }

        number_ /= number;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number power) {
        if constexpr (!std::is_floating_point_v<Number>) {
            if (number_ == Number{} && power == Number{}) {
                return Error("Zero power to zero");
            }
        }

        if constexpr (std::is_same_v<Number, Rational>) {
            if (power.GetDenominator() != 1) {
                return Error("Fractional power is not supported");
            }
            number_ = ::Pow(number_, power);
        } else if constexpr (std::is_integral_v<Number>) {
            if constexpr (std::is_signed_v<Number>) {
                if (power < 0) {
                    return Error("Integer negative power");
                }
            }
            number_ = IntegerPow(number_, power);
        } else {
            number_ = std::pow(number_, power);
        }

        return std::nullopt;
    }

    void Save() {
        memory_ = number_;
    }

    void Load() {
        if (memory_) {
            number_ = *memory_;
        }
    }

    void ClearMem() {
        memory_.reset();
    }

    bool GetHasMem() const {
        return memory_.has_value();
    }

private:
    Number number_{};
    std::optional<Number> memory_;
};
