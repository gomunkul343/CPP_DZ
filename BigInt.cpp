// BIGINT
#include <iomanip>
#include "BigInt.hpp"

void BigInt::ShiftRight() {
    if (numbers_array.empty()) {
        numbers_array.push_back(0);
        return;
    }
    numbers_array.push_back(numbers_array[numbers_array.size() - 1]);
    for (size_t i = numbers_array.size() - 2; i > 0; --i) {
        numbers_array[i] = numbers_array[i - 1];
    }
    numbers_array[0] = 0;
}

bool BigInt::CheckZero(BigInt Number) {  // Проверка на 0.
    if (Number.numbers_array.size() == 1 and Number.numbers_array[0] == 0) {
        return true;
    } else {
        return false;
    }
}

BigInt BigInt::operator+() const {
    return BigInt(*this);
}

BigInt BigInt::operator-() const {
    BigInt c(*this);
    c.sign = !c.sign;
    return c;
}

BigInt &BigInt::operator+=(const BigInt &value) {
    return *this = (*this + value);
}

BigInt &BigInt::operator-=(const BigInt &value) {
    return *this = (*this - value);
}

BigInt &BigInt::operator--() {
    return *this -= BigInt(1);
}

const BigInt BigInt::operator--(int) {
    *this -= BigInt(1);
    return *this + BigInt(1);
}

const BigInt BigInt::operator++(int) {
    *this += BigInt(1);
    return *this - BigInt(1);
}

BigInt &BigInt::operator++() {
    return *this += BigInt(1);
}


bool operator==(const BigInt &left, const BigInt &right) {
    if (left.sign != right.sign) {
        return false;
    }
    if (left.numbers_array.empty()) { // есть конструктор по умолчанию по этому проверка на пустоту
        if (right.numbers_array.empty() || (right.numbers_array.size() == 1 && right.numbers_array[0] == 0)) {
            return true;
        } else {
            return false;
        }
    }
    if (right.numbers_array.empty()) {
        if (left.numbers_array.size() == 1 && left.numbers_array[0] == 0) {
            return true;
        } else {
            return false;
        }
    }
    if (left.numbers_array.size() != right.numbers_array.size()) {
        return false;
    }
    for (size_t i = 0; i < left.numbers_array.size(); ++i) {
        if (left.numbers_array[i] != right.numbers_array[i]) {
            return false;
        }
    }
    return true;
}

bool operator<(const BigInt &left, const BigInt &right) {
    if (left == right) {
        return false;
    }
    if (left.sign) {
        if (right.sign) {
            return ((-right) < (-left));
        } else {
            return true;
        }
    } else if (right.sign) {
        return false;
    } else {
        if (left.numbers_array.size() != right.numbers_array.size()) {
            return left.numbers_array.size() < right.numbers_array.size();
        } else {
            for (long long i = left.numbers_array.size() - 1; i >= 0; --i) {
                if (left.numbers_array[i] != right.numbers_array[i])
                    return left.numbers_array[i] < right.numbers_array[i];
            }
            return false;
        }
    }
}

bool operator<=(const BigInt &left, const BigInt &right) {
    if (left == right) {
        return true;
    }
    if (left < right) {
        return true;
    } else {
        return false;
    }
}

bool operator>(const BigInt &left, const BigInt &right) {
    if (!(left == right) && right < left) {
        return true;
    } else {
        return false;
    }
}

bool operator>=(const BigInt &left, const BigInt &right) {
    if (left == right) {
        return true;
    }
    if (left > right) {
        return true;
    } else {
        return false;
    }
}

BigInt operator+(BigInt left, const BigInt &right) {
    if (left.sign) {
        if (right.sign) {
            return -(-left + (-right));
        } else {
            return right - (-left);
        }
    } else if (right.sign) {
        return left - (-right);
    }
    int carry = 0;
    for (size_t i = 0; i < std::max(left.numbers_array.size(), right.numbers_array.size()) || carry != 0; ++i) {
        if (i == left.numbers_array.size()) {
            left.numbers_array.push_back(0); // добавляем 0, чтобы было возможно сложение, если left < right
        }
        left.numbers_array[i] += carry + (i < right.numbers_array.size() ? right.numbers_array[i] : 0);
        if (left.numbers_array[i] >= BigInt::base) {
            carry = left.numbers_array[i];
        }
        if (carry != 0) {
            left.numbers_array[i] -= BigInt::base;
        }
    }
    return left;
}

BigInt operator-(BigInt left, const BigInt &right) {
    if (right.sign) {
        return left + (-right);
    } else if (left.sign) {
        return -(-left + right);
    } else if (left < right) {
        return -(right - left);
    }
    int carry = 0;
    for (size_t i = 0; i < right.numbers_array.size() || carry; ++i) {
        left.numbers_array[i] -= carry + (i < right.numbers_array.size() ? right.numbers_array[i] : 0);
        carry = left.numbers_array[i] < 0;
        if (carry) {
            left.numbers_array[i] += BigInt::base;
        }
    }
    while (left.numbers_array.size() > 1 && left.numbers_array.back() == 0) {
        left.numbers_array.pop_back();
    }
    return left;
}

BigInt operator*(const BigInt &left, const BigInt &right) {
    BigInt result(0);
    result.numbers_array.resize(left.numbers_array.size() + right.numbers_array.size());
    for (size_t i = 0; i < left.numbers_array.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right.numbers_array.size() || carry != 0; ++j) {
            long long cur = result.numbers_array[i + j] + left.numbers_array[i] * 1LL *
                                                          (j < right.numbers_array.size() ? right.numbers_array[j]
                                                                                          : 0) + carry;
            result.numbers_array[i + j] = cur % BigInt::base;
            carry = cur / BigInt::base;
        }
    }
    while (result.numbers_array.size() > 1 && result.numbers_array.back() == 0) {
        result.numbers_array.pop_back();
    }
    if (left.sign != right.sign) {
        result.sign = true;
    }
    if (left.sign && right.sign) {
        result.sign = false;
    }
    return result;
}

BigInt operator*(BigInt left, const int &right) {
    int carry = 0;
    for (size_t i = 0; i < left.numbers_array.size() || carry; ++i) {
        if (i == left.numbers_array.size()) {
            left.numbers_array.push_back(0);
        }
        long long cur = carry + left.numbers_array[i] * 1ll * right;
        left.numbers_array[i] = int(cur % BigInt::base);
        carry = int(cur / BigInt::base);
    }
    while (left.numbers_array.size() > 1 && left.numbers_array.back() == 0) {
        left.numbers_array.pop_back();
    }
    return left;
}

BigInt operator/(const BigInt &left, const BigInt &right) {
    if (right.numbers_array.size() == 1 and right.numbers_array[0] == 0) {
        std::cout << "divide by 0";
        exit(-1); // защита от любителей делить на 0
    }
    BigInt temp = right;
    temp.sign = false;
    BigInt result(0);
    BigInt current(0);
    result.numbers_array.resize(left.numbers_array.size());
    for (long long i = left.numbers_array.size() - 1; i >= 0; --i) {
        current.ShiftRight();
        current.numbers_array[0] = left.numbers_array[i];
        while (current.numbers_array.size() > 1 && current.numbers_array.back() == 0) {
            current.numbers_array.pop_back();
        }
        int x = 0;
        int y = 0;
        int bbase = BigInt::base;
        while (y <= bbase) {
            int m = (y + bbase) / 2;
            BigInt t = temp * m;
            if (t <= current) {
                x = m;
                y = m + 1;
            } else {
                bbase = m - 1;
            }
        }
        result.numbers_array[i] = x;
        current = current - temp * x;
    }
    if (left.sign != right.sign) {
        result.sign = true;
    }
    while (result.numbers_array.size() > 1 && result.numbers_array.back() == 0) {
        result.numbers_array.pop_back();
    }
    return result;
}

BigInt BigInt::NOD(BigInt num, BigInt den) { //  Нахождение НОДа для сокращения дробей
    BigInt temp1 = std::move(num);
    BigInt temp2 = std::move(den);
    BigInt zero(0);
    temp1.sign = false;
    temp2.sign = false;
    if (temp1 % temp2 == zero) {
        return temp2;
    }
    if (temp2 % temp1 == zero) {
        return temp1;
    }
    if (temp2 < temp1) {
        return NOD(temp1 % temp2, temp2);
    }
    return NOD(temp1, temp2 % temp1);
}


std::ostream &operator<<(std::ostream &strm, const BigInt &BigNum) {
    if (BigNum.numbers_array.empty()) strm << 0;
    else {
        if (BigNum.sign) {
            strm << '-';
        }
        strm << BigNum.numbers_array.back();
        char old_fill = strm.fill('0');
        for (long long i = static_cast<long long>(BigNum.numbers_array.size()) - 2; i >= 0; --i) {
            strm << std::setw(9) << BigNum.numbers_array[i];
        }
        strm.fill(old_fill);
    }
    return strm;
}

BigInt operator%(const BigInt &left, const BigInt &right) {
    BigInt result = left - (left / right) * right;
    if (result.sign) result += right;
    return result;
}

BigInt &BigInt::operator*=(const BigInt &value) {
    return *this = (*this * value);
}

BigInt &BigInt::operator/=(const BigInt &value) {
    return *this = (*this / value);
}

BigInt &BigInt::operator%=(const BigInt &value) {
    return *this = (*this % value);
}


