#ifndef FIXED_CLASS_HPP
#define FIXED_CLASS_HPP

#include <iostream>

// https://spin.atomicobject.com/2012/03/15/simple-fixed-point-math/

class Fixed
{
private:
	static const int _fracBits = 8;
	int _rawBits;
	bool _isNeg;

public:
	Fixed(void);
	Fixed(const int init);
	Fixed(const float init);
	~Fixed(void);
	Fixed(const Fixed &copy);

	Fixed &operator=(const Fixed &rhs);

	bool operator<(const Fixed &rhs) const;
	bool operator<=(const Fixed &rhs) const;
	bool operator>(const Fixed &rhs) const;
	bool operator>=(const Fixed &rhs) const;
	bool operator==(const Fixed &rhs) const;
	bool operator!=(const Fixed &rhs) const;

	Fixed operator+(const Fixed &rhs) const;
	Fixed operator-(const Fixed &rhs) const;
	Fixed operator*(const Fixed &rhs) const;
	Fixed operator/(const Fixed &rhs) const;

	Fixed &operator+=(const Fixed &rhs);
	Fixed &operator-=(const Fixed &rhs);
	Fixed &operator*=(const Fixed &rhs);
	Fixed &operator/=(const Fixed &rhs);

	Fixed &operator++(void);
	Fixed operator++(int);
	Fixed &operator--(void);
	Fixed operator--(int);

	static Fixed max(const Fixed &f1, const Fixed &f2);

	int getRawBits(void) const;
	void setRawBits(const int);
	int toInt() const;
	float toFloat(void) const;
	bool isNeg(void) const;
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif
