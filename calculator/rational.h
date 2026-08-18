#pragma once

#include <cstdint>
#include <iostream>
#include <numeric>
#include <stdexcept>

class Rational {
public:
    Rational(int64_t numerator = 0, int64_t denominator = 1)
        : numerator_(numerator)
        , denominator_(denominator) {
        Normalize();
    }

    int64_t GetNumerator() const {
        return numerator_;
    }

    int64_t GetDenominator() const {
        return denominator_;
    }

    Rational& operator+=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        denominator_ *= other.denominator_;
        Normalize();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        denominator_ *= other.denominator_;
        Normalize();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        Normalize();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        Normalize();
        return *this;
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return {-numerator_, denominator_};
    }

    explicit operator double() const {
        return static_cast<double>(numerator_) / denominator_;
    }

private:
    void Normalize() {
        if (denominator_ == 0) {
            throw std::invalid_argument("zero denominator");
        }
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }

        const int64_t divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int64_t numerator_;
    int64_t denominator_;
};

inline Rational operator+(Rational left, const Rational& right) {
    return left += right;
}

inline Rational operator-(Rational left, const Rational& right) {
    return left -= right;
}

inline Rational operator*(Rational left, const Rational& right) {
    return left *= right;
}

inline Rational operator/(Rational left, const Rational& right) {
    return left /= right;
}

inline bool operator==(const Rational& left, const Rational& right) {
    return left.GetNumerator() == right.GetNumerator()
        && left.GetDenominator() == right.GetDenominator();
}

inline bool operator!=(const Rational& left, const Rational& right) {
    return !(left == right);
}

inline bool operator<(const Rational& left, const Rational& right) {
    return left.GetNumerator() * right.GetDenominator()
        < right.GetNumerator() * left.GetDenominator();
}

inline bool operator>(const Rational& left, const Rational& right) {
    return right < left;
}

inline bool operator<=(const Rational& left, const Rational& right) {
    return !(right < left);
}

inline bool operator>=(const Rational& left, const Rational& right) {
    return !(left < right);
}

inline std::ostream& operator<<(std::ostream& output, const Rational& rational) {
    output << rational.GetNumerator();
    if (rational.GetDenominator() != 1) {
        output << " / " << rational.GetDenominator();
    }
    return output;
}

inline std::istream& operator>>(std::istream& input, Rational& rational) {
    int64_t numerator = 0;
    if (!(input >> numerator)) {
        return input;
    }

    int64_t denominator = 1;
    if (input.eof()) {
        rational = Rational(numerator, denominator);
        return input;
    }
    input >> std::ws;
    if (input.eof()) {
        rational = Rational(numerator, denominator);
        return input;
    }
    if (!input) {
        return input;
    }
    if (input.peek() == '/') {
        input.get();
        if (!(input >> denominator) || denominator == 0) {
            input.setstate(std::ios::failbit);
            return input;
        }
    }

    rational = Rational(numerator, denominator);
    return input;
}
