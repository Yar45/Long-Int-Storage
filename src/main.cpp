#include <iostream>
#include "IntHuge.h"

// Функция для тестирования конструктора по умолчанию
void testDefaultConstructor() {
    bool result = true;

    IntHuge num;
    result &= (num.isNegative() == false);
    result &= (num.getLength() == 0);
    result &= (num.getDigits() == nullptr);
    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "Default Constructor Test" << std::endl;
}

// Функция для тестирования конструктора от строки
void testStringConstructor() {
    bool result = true;

    const char* strNum = "12345678901234567890";
    IntHuge num(strNum);

    result &= (num.isNegative() == false);
    result &= (num.getLength() == 20);
    result &= (num.getDigits()[19] == 0);
    result &= (num.getDigits()[0] == 1);
    result &= (num == "12345678901234567890");

    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "String Constructor Test" << std::endl;
}

// Функция для тестирования конструктора от строки
void testAbsStringConstructor() {
    bool result = true;

    bool isAbs = true;
    const char* strNum = "-12345678901234567890";
    IntHuge num(strNum, isAbs);

    result &= (num.isNegative() == false);
    result &= (num.getLength() == 20);
    result &= (num.getDigits()[19] == 0);
    result &= (num.getDigits()[0] == 1);
    result &= (num == "12345678901234567890");

    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "String Abs Constructor Test" << std::endl;
}

// Функция для тестирования оператора сложения
void testAdditionOperator() {
    bool result = true;

    IntHuge num1("12345678901234567892");
    IntHuge num2("98765432109876543214");
    IntHuge num3("1234");
    IntHuge num4("987654321098765432101213123123");
    IntHuge num5("-98765432109876543214");

    IntHuge result1 = num1 + num2;
    result &= (result1 == "111111111011111111106");

    IntHuge result2 = num1 + num3;
    result &= (result2 == "12345678901234569126");

    IntHuge result3 = num1 + num4;
    result &= (result3 == "987654321111111111002447691015");

    IntHuge result4 = num1 + num5;
    result &= (result4 == "-86419753208641975322");

    IntHuge result5 = num5 + num1;
    result &= (result5 == "-86419753208641975322");

    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "Addition Operator Test" << std::endl;
}

// Функция для тестирования оператора вычитания
void testSubtractionOperator() {
    bool result = true;

    IntHuge num1("98765432109876543214");
    IntHuge num2("12345678901234567892");
    IntHuge num3("1234");
    IntHuge num4("987654321098765432101213123123");
    IntHuge num5("-12345678901234567892");

    IntHuge result1 = num1 - num2;
    result &= (result1 == "86419753208641975322");

    IntHuge result2 = num1 - num3;
    result &= (result2 == "98765432109876541980");

    IntHuge result3 = num1 - num5;
    result &= (result3 == "111111111011111111106");

    IntHuge result4 = num5 - num1;
    result &= (result4 == "-111111111011111111106");

    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "Subtraction Operator Test" << std::endl;
}

// Функция для тестирования оператора умножения
void testMultiplicationOperator() {
    bool result = true;

    IntHuge num1("98765432109876543214");
    IntHuge num2("12345678901234567892");
    IntHuge num3("1234");
    IntHuge num4("987654321098765432101213123123");
    IntHuge num5("-98765432109876543214");
    IntHuge num6("-12345678901234567892");

    IntHuge result1 = num1 * num2;
    result &= (result1 == "1219326311370217952484377380935954884888");

    IntHuge result2 = num1 * num3;
    result &= (result2=="121876543223587654326076");

    IntHuge result3 = num1 * num4;
    result &= (result3=="97546105798506325260845313791630610680648212137322");

    IntHuge result4 = num3 * 2;
    result &= (result4=="2468");

    IntHuge result5 = num3 * 2147483647;
    result &= (result5=="2649994820398");

    IntHuge result6 = num1 * num6;
    result &= (result6 == "-1219326311370217952484377380935954884888");

    IntHuge result7 = num6 * num1;
    result &= (result7 == "-1219326311370217952484377380935954884888");

    IntHuge result8 = num5 * num6;
    result &= (result8 == "1219326311370217952484377380935954884888");

    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "Multiplication Operator Test" << std::endl;
}

// Функция для тестирования операторов сравнения
void testComparisonOperators() {
    bool result = true;

    IntHuge num1("12345678901234567890");
    IntHuge num2("98765432109876543210");
    result &= (num1 < num2);
    result &= (num1 <= num2);
    result &= (!(num1 > num2));
    result &= (!(num1 >= num2));
    result &= (!(num1 == num2));
    result &= (num1 != num2);

    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "Comparison Operators Test" << std::endl;
}

// Функция для тестирования оператора присваивания
void testAssignmentOperator() {
    bool result = true;

    IntHuge num1("12345678901234567890");
    IntHuge num2 = num1;
    result &= (num1 == num2);

    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "Assignment Operator Test" << std::endl;
}

// Функция для тестирования операций по модулю
void testAbsOperator() {
    bool result = true;

    bool isAbs = true;
    IntHuge num1("98765432109876543214", isAbs);
    IntHuge num2("12345678901234567892", isAbs);
    IntHuge num3("-98765432109876543214", isAbs);
    IntHuge num4("-12345678901234567892", isAbs);

    IntHuge result1 = num3 + num4;
    result &= (result1 == "111111111011111111106");

    IntHuge result2 = num2 - num1;
    result &= (result2 == "86419753208641975322");

    IntHuge result3 = num3 - num2;
    result &= (result3 == "86419753208641975322");

    IntHuge result4 = num3 * num4;
    result &= (result4 == "1219326311370217952484377380935954884888");

    IntHuge result5 = num2 * num3;
    result &= (result5 == "1219326311370217952484377380935954884888");

    if (result) std::cout << "Passed: ";
    else std::cout << "Error: ";
    std::cout << "Abs Operations Test" << std::endl;
}

int main() {
    testDefaultConstructor();
    testStringConstructor();
    testAbsStringConstructor();
    testAdditionOperator();
    testSubtractionOperator();
    testMultiplicationOperator();
    testComparisonOperators();
    testAssignmentOperator();
    testAbsOperator();
    return 0;
}