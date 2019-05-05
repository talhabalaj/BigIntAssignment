#include "BigInt.h"
#include <iostream>

using namespace std;


BigInt::BigInt()
{
	setNumber("0");
	setSign(false);
}

BigInt::BigInt(const char* t)
{
	setNumber(t);
	setSign(false);
}

BigInt::BigInt(const char* t, bool a)
{
	setNumber(t);
	setSign(a);
}

BigInt::BigInt(int t)
{
	setNumber(to_string(t).c_str());
	setSign(t < 0);
}

void BigInt::setNumber(const char* t) {
	this->size = strlen(t);
	number.resize(size);
	for (int i = 0; i < size; i++) number[i] = t[size - i - 1];
	if (size > 1) removeInsignificantNumbers();
}

void BigInt::setSign(bool a) {
	this->sign = a;
}


const string BigInt::getNumber() const {
	string s;
	s.resize(size);
	for (int i = 0; i < size; i++) s[i] = number[size - i - 1];
	return s;
}

const bool& BigInt::getSign() {
	return sign;
}

BigInt BigInt::operator+(const BigInt & t) {
	BigInt temp;
	temp.number.pop_back();
	if (this->sign == t.sign) {
		int ll = size > t.size ? size : t.size;
		int ls = size < t.size ? size : t.size;
		int carry = 0;
		for (int i = 0; i < ll; i++) {
			int result = carry;
			if (i < size) {
				int n = number[i] - 48;
				result += n;
			}
			if (i < t.size) {
				int n = t.number[i] - 48;
				result += n;
			}
			if (result > 9) {
				carry = result / 10;
				result /= 10;
			}
			else {
				carry = 0;
			}

			temp.number.push_back(result + 48);
		}
		if (carry != 0) temp.number.push_back(carry + 48);
		temp.sign = sign;
		temp.size = temp.number.length();
		return temp;
	}
	else if (!sign && t.sign) {
		BigInt o = t;
		return o - *this;
	}
	else if (sign && !t.sign) {
		return *this - t;
	}
}

BigInt BigInt::operator-(const BigInt & t) {
	if (size >= t.size) {
		BigInt temp;
		if (t.number == "0") { 
			temp = *this;
			return temp;
		}
		temp.number.pop_back();
		int ll = size > t.size ? size : t.size;
		int ls = size < t.size ? size : t.size;
		bool borrow = 0, carry = 0;
		for (int i = 0; i < ll; i++) {
			int result = 0;
			int n1 = 0;
			int n2 = 0;
			if (i < size) {
				n1 = (number[i] - 48) + carry;
			}

			if (i < t.size) {
				n2 = t.number[i] - 48;
			}

			if (borrow) {
				if (n1 < 1) {
					n1 += 10;
				}
				n1 -= 1;
			}

			if (n1 < n2) {
				borrow = true;
				n1 += 10;
			}

			result = (n1 - n2);

			if (result > 9) {
				carry = result % 10;
				result /= 10;
			}
			else carry = 0;
			temp.number.push_back(result + 48);
		}
		if (carry != 0) temp.number.push_back(carry + 48);
		temp.size = temp.number.length();
		temp.sign = sign;
		return temp;
	}
	else {
		BigInt a = t;
		BigInt temp = a - *this;
		temp.sign = !temp.sign;
		temp.removeInsignificantNumbers();
		return temp;
	}
	
}

BigInt BigInt::absolute() {
	BigInt temp(*this);
	temp.sign = false;
	return temp;
}


ostream & operator<<(ostream & c, const BigInt & d) {
	c << (d.sign ? '-' : '+') << d.getNumber();
	return c;
}

void BigInt::removeInsignificantNumbers() {
	int l = number.length() - 1;
	for (int i = l; number[i] == '0'; i--) {
		number.pop_back();
	}
	this->size = number.length();
}

void BigInt::operator=(const BigInt& b) {
	this->number = b.number;
	this->sign = b.sign;
	this->size = b.size;
}

bool BigInt::operator== ( const BigInt& b) {
	if (size == b.size) {
		for (int i = 0; i < size; i++) {
			if (number[i] != b.number[i]) {
				return false;
			}
		}
		if (sign == b.sign) return true;
	}
	return false;
}
bool BigInt::operator!= (const BigInt& b) {
	return !(*this == b);
}
bool BigInt::operator> (const BigInt& b) {
	if (size > b.size) return true;
	if (number.length() == b.size) {
		bool prevSign = this->sign;
		return ((*this - b).sign == prevSign);
	}
}
bool BigInt::operator< (const BigInt& b) {
	if (size < b.size) return true;
	if (size == b.size) {
		bool prevSign = this->sign;
		return ((*this - b).sign != prevSign);
	}
}
bool BigInt::operator>= (const BigInt& b) {
	return (*this > b || *this == b);
}
bool BigInt::operator<= (const BigInt& b) {
	return (*this < b || *this == b);
}

BigInt BigInt::operator* (const BigInt& b) {
	BigInt temp(*this);
	BigInt mul(b);
	while (mul != 0) {
		temp = temp + b;
	}
	return temp;
}
BigInt BigInt::operator/ (const BigInt& b) {
	BigInt temp(*this);
	BigInt result;
	while (temp >= b) {
		temp = temp - b;
		result = result + 1;
	}
	return result;
}
BigInt BigInt::operator% (const BigInt& b) {
	BigInt temp(*this);
	while (temp >= b) {
		temp = temp - b;
	}
	return temp;
}

//BigInt& BigInt::operator ++() 
//// prefix
//{
//}
//
//
//BigInt  BigInt::operator ++(int) {
//
//}
//BigInt& BigInt::operator --() {
//
//}
//BigInt  BigInt::operator --(int) {
//
//}

BigInt& BigInt::operator+= (const BigInt& b) {
	*this = *this + b;
	return *this;
}
BigInt& BigInt::operator-= (const BigInt& b) {
	*this = *this - b;
	return *this;
}
BigInt& BigInt::operator*= (const BigInt& b) {
	*this = *this * b;
	return *this;
}
BigInt& BigInt::operator/= (const BigInt& b) {
	*this = *this / b;
	return *this;
}
BigInt& BigInt::operator%= (const BigInt& b) {
	*this = *this % b;
	return *this;
}