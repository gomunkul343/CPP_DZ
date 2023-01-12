#include "BigInt.hpp"

#ifndef DISKRETKADZ3_BIGDOUBLE_HPP
#define DISKRETKADZ3_BIGDOUBLE_HPP

class BigDouble { //  Дроби
public:

    BigDouble(std::string &ch, std::string &zn) {
        BigInt num1(ch);
        BigInt den1(zn);
        num = num1;
        den = den1;
    }

    BigDouble(const int &ch, const int &zn) {
        BigInt num1(ch);
        BigInt den1(zn);
        num = num1;
        den = den1;
    }

    friend BigDouble operator+(BigDouble left, const BigDouble &right);

    friend BigDouble operator-(BigDouble left, const BigDouble &right);

    friend BigDouble operator*(BigDouble left, const BigDouble &right);

    friend BigDouble operator/(BigDouble left, const BigDouble &right);

    BigDouble &operator+=(const BigDouble &value);

    BigDouble &operator-=(const BigDouble &value);

    BigDouble &operator*=(const BigDouble &value);

    BigDouble &operator/=(const BigDouble &value);

    BigDouble &operator--();

    BigDouble &operator++();

    const BigDouble operator--(int);

    friend std::ostream &operator<<(std::ostream &strm, BigDouble &BigDouble);

private:
    BigInt num;
    BigInt den;
};

#endif //DISKRETKADZ3_BIGDOUBLE_HPP
