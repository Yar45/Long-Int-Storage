#include "IntHuge.h"

void IntHuge::reset()
{
    delete[] digit;
    digit = nullptr;
    isNegativeNum = false;
    length = 0;
    isAbsCalc = false;
}

void IntHuge::getMinMax(IntHuge** maxInt, IntHuge** minInt, IntHuge* num1, IntHuge* num2) const
{
    if (num1->length == num2->length) {
        if (num1->digit[0] >= num2->digit[0]) {
            *maxInt = num1;
            *minInt = num2;
        }
        else {
            *maxInt = num2;
            *minInt = num1;
        }
    }
    else if (num1->length > num2->length) {
        *maxInt = num1;
        *minInt = num2;
    }
    else {
        *maxInt = num2;
        *minInt = num1;
    }
}

IntHuge::IntHuge(bool _isNegativeNum, unsigned int* _digit, unsigned int _length) : isNegativeNum(_isNegativeNum), isAbsCalc(false)
{
    // Считаем кол-во нулей в начале числа
    unsigned int _offset = 0;
    for (unsigned int i = 0; i < _length; ++i) {
        if (_digit[i] == 0) _offset++;
        else break;
    }

    // Заполняем новый массив без нулей в начале числа
    digit = new unsigned int[_length - _offset];
    for (unsigned int i = 0; i < _length - _offset; ++i) {
        digit[i] = _digit[i + _offset];
    }

    // Ставим длину без нулей в начале
    length = _length - _offset;

    //std::cout << "Init: " << *this << " : IntHuge(bool _isNegativeNum, unsigned int* _digit, unsigned int _length)\n";
}

IntHuge::IntHuge(bool _isNegativeNum, unsigned int* _digit, unsigned int _length, bool _isAbs) : IntHuge(_isNegativeNum, _digit, _length)
{
    isAbsCalc = _isAbs;
}

IntHuge::IntHuge() : isNegativeNum(false), length(0), digit(nullptr), isAbsCalc(false)
{
    //std::cout << "Init: empty : IntHuge()\n";
}

IntHuge::IntHuge(const char* num) : isAbsCalc(false)
{
    // Если передаем что-то неправильное на вход, сразу выдаем ошибку и используем конструктор по-умолчанию
    if (num == nullptr || num[0] == '\0' || (num[0] == '-' && num[1] == '\0')) {
        std::cout << "Value invalid, using base constructor " << std::endl;
        reset();
    } else {
        // Определяем знак
        if (num[0] == '-')
            isNegativeNum = true;
        else 
            isNegativeNum = false;
        
        length = 0;
        unsigned int baseIndex = (isNegativeNum) ? 1 : 0;

        // Перебор массива символов для выяснения длины числа и исключения лишних символов кроме цифр
        for (unsigned int i = baseIndex; num[i] != '\0'; ++i) {
            if (num[i] >= 48 && num[i] <= 57) {
                length++;
            } else {
                std::cout << "Value invalid, using base constructor " << std::endl;
                reset();
                return;
            }
        }

        digit = new unsigned int[length];

        // Перебор массива символов для записи в массив чисел
        for (unsigned int i = 0; i < length; ++i) {
            digit[i] = (int)num[i + baseIndex] - 48; // ascii код в цифру int
        }

        //std::cout << "Init: " << *this << " : IntHuge(const char* num)\n";
    }
}

IntHuge::IntHuge(const char* num, bool isAbs) : isAbsCalc(isAbs)
{
    //*this = IntHuge(num);
    //isNegativeNum = false;

    // Если передаем что-то неправильное на вход, сразу выдаем ошибку и используем конструктор по-умолчанию
    if (num == nullptr || num[0] == '\0' || (num[0] == '-' && num[1] == '\0')) {
        std::cout << "Value invalid, using base constructor " << std::endl;
        reset();
    }
    else {
        // Определяем знак
        if (num[0] == '-')
            isNegativeNum = true;
        else
            isNegativeNum = false;

        length = 0;
        unsigned int baseIndex = (isNegativeNum) ? 1 : 0;

        // Перебор массива символов для выяснения длины числа и исключения лишних символов кроме цифр
        for (unsigned int i = baseIndex; num[i] != '\0'; ++i) {
            if (num[i] >= 48 && num[i] <= 57) {
                length++;
            }
            else {
                std::cout << "Value invalid, using base constructor " << std::endl;
                reset();
                return;
            }
        }

        digit = new unsigned int[length];

        // Перебор массива символов для записи в массив чисел
        for (unsigned int i = 0; i < length; ++i) {
            digit[i] = (int)num[i + baseIndex] - 48; // ascii код в цифру int
        }

        if (isAbs) isNegativeNum = false;

        //std::cout << "Init: " << *this << " : IntHuge(const char* num)\n";
    }
}

IntHuge::~IntHuge()
{
    //std::cout << "Deleting: " << *this << "\n";
    if (digit != nullptr)
        delete[] digit;
}

IntHuge::IntHuge(const IntHuge& num)
{
    //std::cout << "Init: " << *this << " : IntHuge(const IntHuge& num)\n";
    if (digit != nullptr)
        delete[] digit;
    isNegativeNum = num.isNegativeNum;
    length = num.length;
    isAbsCalc = num.isAbsCalc;
    digit = new unsigned int[num.length];
    for (unsigned int i = 0; i < num.length; ++i) {
        digit[i] = num.digit[i];
    }
}

bool IntHuge::isNegative() const
{
    return isNegativeNum;
}

unsigned int* IntHuge::getDigits() const
{
    return digit;
}

unsigned int IntHuge::getLength() const
{
    return length;
}

bool IntHuge::isAbs() const
{
    return isAbsCalc;
}

IntHuge IntHuge::operator+(const IntHuge& num) const
{
    //std::cout << *this;
    //std::cout << " + ";
    //std::cout << num;
    //std::cout << "\n=\n";

    bool currentIsNegativeNum = false;
    if (!isAbsCalc) {
        if (this->isNegativeNum == true) {
            if (num.isNegativeNum == true) {
                // Если оба отрицательные, то складываем, но добавляем минус
                currentIsNegativeNum = true;
            }
            else {
                // Если первое отрицательное, второе положительное, то вычитаем из второго первое, со знаком минус
                return num - *this * (-1);
            }
        } else {
            if (num.isNegativeNum == true) {
                // Если первое положительное, второе отрицательное, то вычитаем из первого второе, со знаком минус
                return *this - (num * (-1));
            }
            else {
                // Если оба положительные, то складываем, не добавляем минус
                currentIsNegativeNum = false;
            }
        }
    }

    unsigned int newLength;
    unsigned int indexOffset;
    IntHuge* maxInt = nullptr;
    IntHuge* minInt = nullptr;

    // Определяем какое число больше
    getMinMax(&maxInt, &minInt, (IntHuge*)this, &const_cast<IntHuge&>(num));

    newLength = maxInt->length + 1;
    indexOffset = maxInt->length - minInt->length;

    // Заполняем новый массив нулями, а потом заолняем максимальным числом
    unsigned int* newDigitList = new unsigned int[newLength] {0};
    for (unsigned int i = 0; i < newLength; ++i) {
        newDigitList[i + 1] = maxInt->digit[i];
    }

    // Сложение
    unsigned int sum = 0;
    for (unsigned int i = newLength - 1; i >= indexOffset + 1; i--) {
        sum += newDigitList[i] + minInt->digit[i - indexOffset - 1];
        sum += newDigitList[i - 1] * 10;

        newDigitList[i] = sum % 10;
        newDigitList[i - 1] = sum / 10;

        sum = 0;
    }
    //std::cout << "\n";
    return IntHuge(currentIsNegativeNum, newDigitList, newLength, isAbsCalc);
}

IntHuge& IntHuge::operator+=(const IntHuge& num) {
    *this = *this + num;
    return *this;
}

IntHuge IntHuge::operator-(const IntHuge& num) const
{
    //std::cout << *this;
    //std::cout << " - ";
    //std::cout << num;
    //std::cout << "\n=\n";

    bool currentIsNegativeNum = false;
    if (!isAbsCalc) {
        if (this->isNegativeNum == true) {
            if (num.isNegativeNum == true) {
                // Если оба отрицательные, то итоговое отрицательное, итоговое = первое + второе
                return *this + num;
            }
            else {
                // Если первое отрицательное, второе положительное, то итоговое отрицательное, итоговое = первое - второе
                return (*this * (-1) + num) * (-1);
            }
        }
        else {
            if (num.isNegativeNum == true) {
                // Если первое положительное, второе отрицательное, то итоговое = первое + второе
                return *this + num * (-1);
            }
        }
    }

    unsigned int newLength;
    unsigned int indexOffset;
    IntHuge* maxInt = nullptr;
    IntHuge* minInt = nullptr;

    // Определяем какое число больше
    getMinMax(&maxInt, &minInt, (IntHuge*)this, &const_cast<IntHuge&>(num));
    
    // Если оба положительные, просто вычитаем, определяя знак, сходя из того, какое число больше
    if (!isAbsCalc) {
        if (this->length == num.length) {
            if (this->digit[0] >= num.digit[0]) {
                currentIsNegativeNum = false;
            }
            else {
                currentIsNegativeNum = true;
            }
        }
        else if (this->length > num.length) {
            currentIsNegativeNum = false;
        }
        else {
            currentIsNegativeNum = true;
        }
    }
    //std::cout << "IS_MINUS: " << currentIsNegativeNum << " |";

    newLength = maxInt->length + 1;
    indexOffset = maxInt->length - minInt->length;

    // Заполняем новый массив нулями, а потом заполняем первым числом
    unsigned int* newDigitList = new unsigned int[newLength] {0};
    for (unsigned int i = 0; i < newLength; ++i) {
        newDigitList[i + 1] = maxInt->digit[i];
    }

    // Вычитание
    unsigned int sum = 0;
    for (unsigned int i = newLength - 1; i >= indexOffset + 1; i--) {
        sum += newDigitList[i - 1] * 10 + newDigitList[i];
        sum -= minInt->digit[i - indexOffset - 1];

        newDigitList[i] = sum % 10;
        newDigitList[i - 1] = sum / 10;

        sum = 0;
    }
    //std::cout << "\n";
    return IntHuge(currentIsNegativeNum, newDigitList, newLength, isAbsCalc);
}

IntHuge& IntHuge::operator-=(const IntHuge& num)
{
    *this = *this - num;
    return *this;
}

IntHuge IntHuge::operator*(const IntHuge& num) const
{
    //std::cout << "* ";
    unsigned int newLength;
    IntHuge* maxInt = nullptr;
    IntHuge* minInt = nullptr;

    // Определяем какое число больше
    getMinMax(&maxInt, &minInt, (IntHuge*)this, &const_cast<IntHuge&>(num));

    newLength = maxInt->length + minInt->length;

    // Умножение
    unsigned int* newDigitList = new unsigned int[newLength] {0};
    unsigned int* newDigitListInverse = new unsigned int[newLength] {0};

    for (unsigned int i = 0; i < maxInt->length; ++i) {
        for (unsigned int j = 0; j < minInt->length; ++j) {
            newDigitList[i + j] += maxInt->digit[maxInt->length - i - 1] * minInt->digit[minInt->length - j - 1];
            newDigitList[i + j + 1] += newDigitList[i + j] / 10;
            newDigitList[i + j] %= 10;
        }
    }

    for (unsigned int i = 0; i < newLength - 1; ++i) {
        newDigitList[i + 1] += newDigitList[i] / 10;
        newDigitList[i] %= 10;
    }

    // Инвертируем
    for (unsigned int i = 0; i < newLength; ++i) {
        newDigitListInverse[i] = newDigitList[newLength - i - 1];
    }

    delete[] newDigitList;
    //std::cout << "\n";
    if (!isAbsCalc) return IntHuge(maxInt->isNegativeNum ^ minInt->isNegativeNum, newDigitListInverse, newLength);
    else return IntHuge(false, newDigitListInverse, newLength, isAbsCalc);
}

IntHuge& IntHuge::operator*=(const IntHuge& num)
{
    *this = *this * num;
    return *this;
}

IntHuge IntHuge::operator*(int num) const
{
    if (num == -1) {
        if (this->isNegativeNum) return IntHuge(false, this->digit, this->length);
        else return IntHuge(true, this->digit, this->length);
    }

    // Число в строку, затем умножаем как обычно
    char str[11]{0};
    _itoa_s(num, str, 11, 10);
    return *this * IntHuge(str, isAbsCalc);
}

IntHuge& IntHuge::operator*=(int num)
{
    *this = *this * num;
    return *this;
}

bool IntHuge::operator==(const char* num) const
{
    //std::cout << "\n%" << num << "%\n";
    unsigned int baseIndex = (num[0] == '-') ? 1 : 0;
    unsigned int _length = 0;

    if (!isAbsCalc) {
        // Сравниваем знаки отрицания
        if (isNegativeNum != baseIndex)
            return false;
    }

    // Находим длину
    for (unsigned int i = baseIndex; num[i] != '\0'; ++i) {
        if (num[i] >= 48 && num[i] <= 57) {
            _length++;
        }
        else {
            //std::cout << num[i];
            std::cout << "Value invalid" << std::endl;
            return false;
        }
    }

    // Сравниваем длину
    if (_length != length)
        return false;

    // Сравниваем знаки числа
    for (unsigned int i = 0; i < _length; ++i) {
        if (digit[i] != (int)num[i + baseIndex] - 48) // ascii код в цифру int
            return false;
    }

    return true;
}

bool IntHuge::operator==(const IntHuge& num) const
{
    if (!isAbsCalc) if (isNegativeNum != num.isNegativeNum) return false;
    if (length != num.length) return false;

    for (unsigned int i = 0; i < length; ++i) {
        if (digit[i] != num.digit[i]) return false;
    }
    return true;
}

bool IntHuge::operator!=(const IntHuge& num) const
{
    if (!isAbsCalc) if (isNegativeNum != num.isNegativeNum) return true;
    if (length != num.length) return true;

    for (unsigned int i = 0; i < length; ++i) {
        if (digit[i] != num.digit[i]) return true;
    }

    return false;
}

bool IntHuge::operator>(const IntHuge& num) const
{
    if (!isAbsCalc) if (!isNegativeNum && num.isNegativeNum) return true;
    if (length > num.length) return true;
    else if (length < num.length) return false;
    else {
        for (unsigned int i = 0; i < length; ++i) {
            if (digit[i] > num.digit[i]) return true;
            else if (digit[i] < num.digit[i]) return false;
        }
    }
    return false;
}

bool IntHuge::operator<(const IntHuge& num) const
{
    if (!isAbsCalc) if (isNegativeNum && !num.isNegativeNum) return true;
    if (length > num.length) return false;
    else if (length < num.length) return true;
    else {
        for (unsigned int i = 0; i < length; ++i) {
            if (digit[i] > num.digit[i]) return false;
            else if (digit[i] < num.digit[i]) return true;
        }
    }
    return false;
}

bool IntHuge::operator>=(const IntHuge& num) const
{
    return (*this > num) || (*this == num);
}

bool IntHuge::operator<=(const IntHuge& num) const
{
    return (*this < num) || (*this == num);
}

std::ostream& operator<<(std::ostream& os, const IntHuge& num)
{
    if (num.digit == nullptr)
        return os << "empty";

    if (num.isNegativeNum) {
        os << '-';
    }

    for (unsigned int i = 0; i < num.length; ++i) {
        os << num.digit[i];
    }

    return os;
}

std::istream& operator>>(std::istream& is, IntHuge& num)
{
    // Считываем в строку, инициализируем через строковый конструктор, максимальный длина определяется через #define в IntHuge.h
    char buff[MAX_STRING_INPUT_LEN];
    is >> buff;
    num = IntHuge(buff);
    return is;
}
