#include <iostream>
#include <vector>
#include <string>

#ifndef DISKRETKADZ3_BIGINT_HPP
#define DISKRETKADZ3_BIGINT_HPP

class BigInt {
public:
    BigInt() {};

    explicit BigInt(std::string &number) {
        if (number[0] == '-') {
            number = number.substr(1);
            sign = true;
        } else {
            sign = false;
        }
        for (int i = number.length(); i > 0; i -= 9) {
            numbers_array.push_back(atoi((i < 9 ? number.substr(0, i) : number.substr(i - 9, 9)).c_str()));
        }
    }
    // Конструкторы с одним аргументом должны быть помечены как явные, чтобы избежать непреднамеренных неявных преобразований (Clang-tidy подсвечивал)
    explicit BigInt(int number) {
        if (number < 0) {
            sign = true;
            number = number;
        } else {
            sign = false;
        }
        while (number != 0) {
            numbers_array.push_back(number % base);
            number /= base;
        }
    }

    void ShiftRight();

    static bool CheckZero(BigInt Number);

    static BigInt NOD(BigInt num, BigInt den);

    //унарные знаки
    BigInt operator+() const;

    BigInt operator-() const;

    BigInt &operator+=(const BigInt &value);

    BigInt &operator-=(const BigInt &value);

    BigInt &operator*=(const BigInt &value);

    BigInt &operator/=(const BigInt &value);

    BigInt &operator%=(const BigInt &value);

    // инкремент и декремент
    BigInt &operator--();

    const BigInt operator--(int);

    BigInt &operator++();

    const BigInt operator++(int);


    // операторы сравнения
    friend bool operator==(const BigInt &left, const BigInt &right);

    friend bool operator<(const BigInt &left, const BigInt &right);

    friend bool operator<=(const BigInt &left, const BigInt &right);

    friend bool operator>(const BigInt &left, const BigInt &right);

    friend bool operator>=(const BigInt &left, const BigInt &right);

    // сложение
    friend BigInt operator+(BigInt left, const BigInt &right);

    // вычитание
    friend BigInt operator-(BigInt left, const BigInt &right);

    // умножение BigInt на BigInt
    friend BigInt operator*(const BigInt &left, const BigInt &right);

    // умножениие BigInt на int
    friend BigInt operator*(BigInt left, const int &right);

    // деление BigInt на BigInt
    friend BigInt operator/(const BigInt &left, const BigInt &right);

    friend std::ostream &operator<<(std::ostream &strm, const BigInt &BigNum);

    friend BigInt operator%(const BigInt &left, const BigInt &right);

private:
    static const int base = 1000000000;
    bool sign;
    std::vector<int> numbers_array;
};


#endif //DISKRETKADZ3_BIGINT_HPP




