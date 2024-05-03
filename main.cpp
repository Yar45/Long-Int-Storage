#include <iostream>
#include <algorithm>
#include <string>

class IntHuge {
private:
    int* data;
    int size;

public:
    IntHuge() {
        size = 1;
        data = new int[size];
        data[0] = 0;
    }

    IntHuge(const IntHuge& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~IntHuge() {
        delete[] data;
    }

    void set(int index, int value) {
        if (index < size && index >= 0) {
            data[index] = value;
        }
    }

    int get(int index) const {
        if (index < size && index >= 0) {
            return data[index];
        }
        return 0;
    }

    IntHuge(const std::string& number) {
        size = number.length();
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = number[i] - '0';
        }
    }

    IntHuge& operator=(const IntHuge& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    IntHuge& operator+=(const IntHuge& other) {
        int maxSize = std::max(size, other.size);
        int carry = 0;
        int* newData = new int[maxSize + 1];

        for (int i = 0; i < maxSize; i++) {
            int sum = carry + get(i) + other.get(i);
            newData[i] = sum % 10;
            carry = sum / 10;
        }

        if (carry > 0) {
            newData[maxSize] = carry;
            maxSize++;
        }

        delete[] data;
        data = newData;
        size = maxSize;

        return *this;
    }

    IntHuge& operator-=(const IntHuge& other) {
        *this >= other;
        int borrow = 0;

        for (int i = 0; i < size; i++) {
            int diff = data[i] - (i < other.size) - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            data[i] = diff;
        }

        while (size > 1 && data[size - 1] == 0) {
            size--;
        }

        return *this;
    }

    bool operator==(const IntHuge& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator<(const IntHuge& other) const {
        if (size != other.size) return size < other.size;
        for (int i = size - 1; i >= 0; i--) {
            if (data[i] != other.data[i]) return data[i] < other.data[i];
        }
        return false;
    }

    IntHuge operator*(int multiplier) const {
        IntHuge result;
        result.size = size + std::to_string(multiplier).length();
        delete[] result.data;
        result.data = new int[result.size]();

        int carry = 0;

        for (int i = 0; i < size; i++) {
            int product = data[i] * multiplier + carry;
            result.data[i] = product % 10;
            carry = product / 10;
        }

        int i = size;
        while (carry > 0) {
            result.data[i++] = carry % 10;
            carry /= 10;
        }

        while (i > 1 && result.data[i - 1] == 0) {
            i--;
        }
        result.size = i;

        return result;
    }

    IntHuge operator-(const IntHuge& other) const {
        IntHuge result = *this;
        result -= other;
        return result;
    }

    bool operator>(const IntHuge& other) const {
        return other < *this;
    }

    bool operator<=(const IntHuge& other) const {
        return !(*this > other);
    }

    bool operator>=(const IntHuge& other) const {
        return !(*this < other);
    }

    IntHuge operator*(const IntHuge& other) const {
        IntHuge result;
        result.size = size + other.size;
        delete[] result.data;
        result.data = new int[result.size]();

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < other.size; ++j) {
                result.data[i + j] += data[i] * other.data[j];
                result.data[i + j + 1] += result.data[i + j] / 10;
                result.data[i + j] %= 10;
            }
        }

        while (result.size > 1 && result.data[result.size - 1] == 0) {
            result.size--;
        }

        return result;
    }

    IntHuge& operator*=(const IntHuge& other) {
        *this = *this * other;
        return *this;
    }

    IntHuge operator+(const IntHuge& other) const {
        IntHuge sum = *this;
        sum += other; 
        return sum;
    }

    bool operator!=(const IntHuge& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out, const IntHuge& huge) {
        for (int i = huge.size - 1; i >= 0; i--) {
            out << huge.data[i];
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, IntHuge& huge) {
        std::string number;
        in >> number;

        std::reverse(number.begin(), number.end());

        delete[] huge.data;

        huge.size = number.length();
        huge.data = new int[huge.size];
        for (int i = 0; i < huge.size; ++i) {
            huge.data[i] = number[i] - '0';
        }

        return in;
    }
};

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