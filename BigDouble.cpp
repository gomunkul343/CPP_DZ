// BIGDOUBLE
#include "BigDouble.hpp"

std::ostream &operator<<(std::ostream &strm, BigDouble &BigDouble) {
    if (BigDouble.num.CheckZero(BigDouble.num)) {
        strm << "0";
        return strm;
    }
    if (BigDouble.den.CheckZero(BigDouble.den)) {
        std::cout << "Divide by zero";
        exit(-1);
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
    return *this += BigDouble(1, 1);
}

BigDouble BigDouble::operator--(int) &{
    *this -= BigDouble(1, 1);
    return *this + BigDouble(1, 1);
}

BigDouble BigDouble::operator++(int) &{
    *this += BigDouble(1, 1);
    return *this - BigDouble(1, 1);
}

bool operator==(const BigDouble &left, const BigDouble &right) {
    BigInt zero(0);
    if (left.den == zero || right.den == zero) {
        std::cout << "divide by zero" << std::endl;
        exit(-3);
    }
    if (left.Sign() == right.Sign()) {
        if (BigInt::CompareUnsigned(left.num * right.den, right.num * left.den)) {
            return true;
        }
        return false;
    }
    return false;
}

bool operator<(const BigDouble &left, const BigDouble &right) {
    BigInt zero(0);
    if (left.den == zero || right.den == zero) {
        std::cout << "divide by zero" << std::endl;
        exit(-3);
    }
    if (!(left == right)) {
        if (left.den == right.den) {
            return left.num < right.num;
        } else if (left.Sign() <= right.Sign()) {
            BigInt num1;
            num1 = BigInt::MultiplyWithoutSign(left.num, right.den);
            BigInt num2;
            num2 = BigInt::MultiplyWithoutSign(right.num, right.num);
            return num1 < num2;
        }
    }
    return false;
}

bool operator<=(const BigDouble &left, const BigDouble &right) {
    if (left == right) {
        return true;
    }
    if (left < right) {
        return true;
    } else {
        return false;
    }
}

bool operator>(const BigDouble &left, const BigDouble &right) {
    if (!(left == right) && right < left) {
        return true;
    } else {
        return false;
    }
}

bool operator>=(const BigDouble &left, const BigDouble &right) {
    if (left == right) {
        return true;
    }
    if (left > right) {
        return true;
    } else {
        return false;
    }
}

bool BigDouble::Sign() const {
    return num.GetSign() ^ den.GetSign();
}




