#include "BigDouble.hpp"

std::ostream &operator<<(std::ostream &strm, BigDouble &BigDouble) {
    if (BigDouble.num.CheckZero(BigDouble.num)) {
        strm << "0";
        return strm;
    }
    if (BigDouble.den.CheckZero(BigDouble.den)) {
        std::cout << "Divide by zero";
        return strm;
    }
    BigInt c;
    c = BigInt::NOD(BigDouble.num, BigDouble.den);
    BigDouble.num = BigDouble.num / c;
    BigDouble.den = BigDouble.den / c;
    strm << BigDouble.num << "/" << BigDouble.den;
    return strm;
}

BigDouble operator+(BigDouble left, const BigDouble &right) {
    left.num = left.num * right.den + right.num * left.den;
    left.den = left.den * right.den;
    return left;
}

BigDouble operator-(BigDouble left, const BigDouble &right) {
    left.num = left.num * right.den - right.num * left.den;
    left.den = left.den * right.den;
    return left;
}

BigDouble operator*(BigDouble left, const BigDouble &right) {
    left.num = left.num * right.num;
    left.den = left.den * right.den;
    return left;
}

BigDouble operator/(BigDouble left, const BigDouble &right) {
    left.num = left.num * right.den;
    left.den = left.den * right.num;
    return left;
}

BigDouble &BigDouble::operator+=(const BigDouble &value) {
    return *this = (*this + value);
}

BigDouble &BigDouble::operator-=(const BigDouble &value) {
    return *this = (*this - value);
}

BigDouble &BigDouble::operator*=(const BigDouble &value) {
    return *this = (*this * value);
}

BigDouble &BigDouble::operator/=(const BigDouble &value) {
    return *this = (*this / value);
}

BigDouble &BigDouble::operator--() {
    return *this -= BigDouble(1, 1);
}

BigDouble &BigDouble::operator++() {
    return *this -= BigDouble(1, 1);
}

const BigDouble BigDouble::operator--(int) {
    *this -= BigDouble(1, 1);
    return *this + BigDouble(1, 1);
}



