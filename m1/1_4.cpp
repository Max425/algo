// Инвертируйте значение бита в числе N по его номеру K.

#include <iostream>
#include <cassert>

void invertKPositionInNumber(unsigned int &number, unsigned int kPosition) {
    assert(kPosition <= 31);

    number ^= 1 << kPosition; // Используем XOR с маской 1 << kPosition
}

int main() {
    unsigned int number, kPosition;
    std::cin >> number >> kPosition;
    invertKPositionInNumber(number, kPosition);
    std::cout << number << std::endl;
    return 0;
}