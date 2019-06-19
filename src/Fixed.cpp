#include <Fixed.hpp>
#include <cmath>

Fixed::Fixed(void) : _rawBits(0), _isNeg(false) {}

Fixed::Fixed(const int init) : _rawBits(0), _isNeg(false)
{
	int val = init;
	if (val < 1)
	{
		val = val * -1;
		this->_isNeg = true;
	}
	this->_rawBits = val << Fixed::_fracBits;
}

Fixed::Fixed(const float init) : _rawBits(0), _isNeg(false)
{
	float val = init;
	if (val < 1)
	{
		val = val * -1;
		this->_isNeg = true;
	}
	this->_rawBits = roundf(val * (1 << Fixed::_fracBits));
}

Fixed::~Fixed(void) {}

Fixed::Fixed(const Fixed &copy)
{
	*this = copy;
}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	if (this != &rhs)
	{
		this->_isNeg = rhs._isNeg;
		this->_rawBits = rhs._rawBits;
	}
	return (*this);
}

bool Fixed::operator<(const Fixed &rhs) const
{
	if (this->_isNeg == rhs._isNeg)
	{
		if (this->_isNeg)
			return this->_rawBits > rhs._rawBits;
		return this->_rawBits < rhs._rawBits;
	}
	return this->_isNeg > rhs._isNeg;
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return *this < rhs || *this == rhs;
}

bool Fixed::operator>(const Fixed &rhs) const
{
	return !(*this <= rhs);
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return *this > rhs || *this == rhs;
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return (this->_rawBits == rhs._rawBits) && (this->_isNeg == rhs._isNeg);
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return !(*this == rhs);
}

Fixed Fixed::operator+(const Fixed &rhs) const
{
	Fixed ret(*this);
	ret += rhs;
	return ret;
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	Fixed tmp(rhs);
	tmp._isNeg = !tmp._isNeg;
	return *this + tmp;
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	Fixed ret(*this);
	ret *= rhs;
	return ret;
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	Fixed ret(*this);
	ret /= rhs;
	return ret;
}

Fixed &Fixed::operator+=(const Fixed &rhs)
{
	Fixed ret;
	if (this->_isNeg == rhs._isNeg)
	{
		this->setRawBits(this->_rawBits + rhs._rawBits);
		return (*this);
	}
	else if (rhs._isNeg)
		this->setRawBits(this->_rawBits - rhs._rawBits);
	else
		this->setRawBits(rhs._rawBits - this->_rawBits);

	return (*this);
}

Fixed &Fixed::operator-=(const Fixed &rhs)
{
	Fixed tmp(rhs);
	tmp._isNeg = !tmp._isNeg;
	*this += tmp;
	return (*this);
}

Fixed &Fixed::operator*=(const Fixed &rhs)
{
	int val = ((long long)this->getRawBits() * (long long)rhs.getRawBits()) / (1 << Fixed::_fracBits);
	this->setRawBits(val);
	this->_isNeg = (this->_isNeg != rhs._isNeg);
	return (*this);
}

Fixed &Fixed::operator/=(const Fixed &rhs)
{
	long long val = (((long long)this->getRawBits()) * (1 << Fixed::_fracBits)) / rhs.getRawBits();
	this->setRawBits(val);
	this->_isNeg = (this->_isNeg != rhs._isNeg);
	return (*this);
}

Fixed &Fixed::operator++(void)
{
	this->_rawBits++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	this->_rawBits++;
	return tmp;
}

Fixed &Fixed::operator--(void)
{
	this->_rawBits--;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	this->_rawBits--;
	return (tmp);
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}

Fixed Fixed::max(const Fixed &f1, const Fixed &f2)
{
	return Fixed(f1 >= f2 ? f1 : f2);
}

int Fixed::getRawBits(void) const
{
	return this->_rawBits;
}

void Fixed::setRawBits(int const rawBits)
{
	this->_rawBits = rawBits;
	if (this->_rawBits < 0)
	{
		this->_isNeg = true;
		this->setRawBits(this->_rawBits * -1);
	}
}

bool Fixed::isNeg(void) const
{
	return this->_isNeg;
}

int Fixed::toInt(void) const
{
	int ret = (_rawBits >> Fixed::_fracBits);
	ret *= (this->_isNeg) ? -1 : 1;
	return ret;
}

float Fixed::toFloat(void) const
{
	float ret = this->_rawBits;
	ret /= 1 << Fixed::_fracBits;
	ret *= (this->_isNeg) ? -1 : 1;
	return ret;
}
