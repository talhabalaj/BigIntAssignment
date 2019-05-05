#include <iostream>
#include <string>

using namespace std;

class BigInt
{
private:
	string number;
	int size;
	bool sign; // 1 for negative
public:
	BigInt();
	BigInt(const char*);
	BigInt(const char*, bool);
	BigInt(int);

	void setNumber(const char*);
	void setSign(bool);
	const string getNumber() const;
	const bool& getSign();

	BigInt operator+(const BigInt&);
	BigInt operator-(const BigInt&);
	BigInt operator * (const BigInt& b);
	BigInt operator / (const BigInt& b);
	BigInt operator % (const BigInt& b);

	BigInt& operator ++(); // prefix
	BigInt operator ++(int); // postfix
	BigInt& operator --(); // prefix
	BigInt operator --(int); // postfix

	BigInt absolute(); // returns the absolute value
	void operator= (const BigInt& b);
	bool operator== (const BigInt& b);
	bool operator!= (const BigInt& b);
	bool operator> (const BigInt& b);
	bool operator< (const BigInt& b);
	bool operator>= (const BigInt& b);
	bool operator<= (const BigInt& b);

	BigInt& operator+= (const BigInt& b);
	BigInt& operator-= (const BigInt& b);
	BigInt& operator*= (const BigInt& b);
	BigInt& operator/= (const BigInt& b);
	BigInt& operator%= (const BigInt& b);

	friend ostream& operator<<(ostream&, const BigInt&);
	void removeInsignificantNumbers();
};

