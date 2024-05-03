#include <iostream>
#include <algorithm>
#include <string>

class IntHuge {
private:
    int* data;
    int size;

public:
    IntHuge();

    IntHuge(const IntHuge& other);

    ~IntHuge();

    void set(int index, int value);

    int get(int index) const;

    IntHuge(const std::string& number);

    IntHuge& operator=(const IntHuge& other);

    IntHuge& operator+=(const IntHuge& other);

    IntHuge& operator-=(const IntHuge& other);

    bool operator==(const IntHuge& other) const;

    bool operator<(const IntHuge& other) const;

    IntHuge operator*(int multiplier) const;

    IntHuge operator-(const IntHuge& other) const;

    bool operator>(const IntHuge& other) const;
    bool operator<=(const IntHuge& other) const;

    bool operator>=(const IntHuge& other) const;

    IntHuge operator*(const IntHuge& other) const;

    IntHuge& operator*=(const IntHuge& other);

    IntHuge operator+(const IntHuge& other) const;

    bool operator!=(const IntHuge& other) const;

    friend std::ostream& operator<<(std::ostream& out, const IntHuge& huge);

    friend std::istream& operator>>(std::istream& in, IntHuge& huge);
};