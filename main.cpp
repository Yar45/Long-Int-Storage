#include <iostream>
#include "IntHuge.h"

int main() {
    IntHuge a, b, result;

    std::cout << "Input a: ";
    std::cin >> a;

    std::cout << "Input b: ";
    std::cin >> b;

    result = a;
    std::cout << "result = a: " << result << std::endl;

    result = a + b;
    std::cout << "a + b: " << result << std::endl;

    a += b;
    std::cout << "a += b: " << a << std::endl;

    result = a - b;
    std::cout << "a - b: " << result << std::endl;

    a -= b;
    std::cout << "a -= b: " << a << std::endl;

    if (a == b) {
        std::cout << "a == b: true" << std::endl;
    }
    else {
        std::cout << "a == b: false" << std::endl;
    }

    if (a != b) {
        std::cout << "a != b: true" << std::endl;
    }
    else {
        std::cout << "a != b: false" << std::endl;
    }

    if (a > b) {
        std::cout << "a > b: true" << std::endl;
    }
    else {
        std::cout << "a > b: false" << std::endl;
    }

    if (a < b) {
        std::cout << "a < b: true" << std::endl;
    }
    else {
        std::cout << "a < b: false" << std::endl;
    }

    if (a >= b) {
        std::cout << "a >= b: true" << std::endl;
    }
    else {
        std::cout << "a >= b: false" << std::endl;
    }

    if (a <= b) {
        std::cout << "a <= b: true" << std::endl;
    }
    else {
        std::cout << "a <= b: false" << std::endl;
    }

    result = a * b;
    std::cout << "a * b: " << result << std::endl;

    a *= b;
    std::cout << "a *= b: " << a << std::endl;

    int multiplier = 3;
    result = a * multiplier;
    std::cout << "a * multiplier: " << result << std::endl;

    return 0;
}