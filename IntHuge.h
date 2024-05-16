#pragma once

#include <iostream>

#define MAX_STRING_INPUT_LEN 256

class IntHuge
{
private:
	bool isNegativeNum;
	unsigned int* digit;
	unsigned int length;

	bool isAbsCalc;

	void reset();
	void getMinMax(IntHuge** maxInt, IntHuge** minInt, IntHuge* num1, IntHuge* num2) const;

	IntHuge(bool _isNegativeNum, unsigned int* _digit, unsigned int _length);
	IntHuge(bool _isNegativeNum, unsigned int* _digit, unsigned int _length, bool _isAbs);
public:
	IntHuge();
	IntHuge(const char* num);
	IntHuge(const char* num, bool isAbs);
	IntHuge(const IntHuge& num);
	~IntHuge();

	bool isNegative() const;
	unsigned int* getDigits() const;
	unsigned int getLength() const;
	bool isAbs() const;

	IntHuge operator + (const IntHuge& num) const;
	IntHuge& operator += (const IntHuge& num);
	IntHuge operator - (const IntHuge& num) const;
	IntHuge& operator -= (const IntHuge& num);
	IntHuge operator * (const IntHuge& num) const;
	IntHuge& operator *= (const IntHuge& num);
	IntHuge operator * (int num) const;
	IntHuge& operator *= (int num);

	bool operator == (const char* num) const;
	bool operator == (const IntHuge& num) const;
	bool operator != (const IntHuge& num) const;
	bool operator > (const IntHuge& num) const;
	bool operator < (const IntHuge& num) const;
	bool operator >= (const IntHuge& num) const;
	bool operator <= (const IntHuge& num) const;

	friend std::ostream& operator<<(std::ostream& os, const IntHuge& num);
	friend std::istream& operator>>(std::istream& is, IntHuge& num);
};