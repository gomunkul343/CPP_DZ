#include "BigInt.hpp"
#include "BigDouble.hpp"

int main() {
    std::string enternum1;
    std::string enternum2;
    std::cin >> enternum1 >> enternum2;
    BigInt num1(enternum1);
    BigInt num2(enternum2);
    --num1;
    num1--;
    num1++;
    ++num1;
    std::cout << num1 << std::endl;
    BigInt sum = num1 + num2;
    std::cout << sum << std::endl;
    BigInt z = num1 - num2;
    std::cout << z << std::endl;
    BigInt q = num1 * num2;
    std::cout << q << std::endl;
    z = num1 / num2;
    std::cout << z << std::endl;
    std::string enterden1;
    std::string enterden2;
    std::cin >> enterden1 >> enterden2;
    BigDouble fract1(enternum1, enterden1);
    fract1 += fract1;
    --fract1;
    fract1 /= fract1;
    std::cout << fract1 << std::endl;
    BigDouble fract2(enternum2, enterden2);
    fract1 = fract1 * fract2;
    std::cout << fract1 << std::endl;
    fract1 = fract1 / fract2;
    std::cout << fract1 << std::endl;
    fract1 = fract1 + fract2;
    std::cout << fract1 << std::endl;
    fract1 = fract1 - fract2;
    std::cout << fract1 << std::endl;
    return 0;
}
