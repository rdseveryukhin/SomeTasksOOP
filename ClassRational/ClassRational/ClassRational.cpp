#include <iostream>

struct Rational {
	Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) {};

	void add(Rational rational) {
		numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
		denominator_ *= rational.denominator_;
	}

	void sub(Rational rational) {
		numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
		denominator_ *= rational.denominator_;
	}

	void mul(Rational rational) {
		numerator_ *= rational.numerator_;
		denominator_ *= rational.denominator_;
	}

	void div(Rational rational) {
		numerator_ *= rational.denominator_;
		denominator_ *= rational.numerator_;
	}

	void neg() {
		numerator_ = -numerator_;
	}

	void inv() {}

	double to_double() const {
		return numerator_ / (double)denominator_;
	}

	int get_numerator() {
		return this->numerator_;
	}

	int get_denominator() {
		return this->denominator_;
	}


	Rational& operator += (const Rational& rational) {
		this->add(rational);
		return *this;
	}

	Rational& operator += (int d) {
		this->add(Rational(d));
		return *this;
	}

	Rational& operator -= (const Rational& rational) {
		this->sub(rational);
		return *this;
	}

	Rational& operator -= (int d) {
		this->sub(Rational(d));
		return *this;
	}

	Rational& operator *= (const Rational& rational) {
		this->mul(rational);
		return *this;
	}

	Rational& operator *= (int d) {
		this->mul(Rational(d));
		return *this;
	}

	Rational& operator /= (const Rational& rational) {
		this->div(rational);
		return *this;
	}

	Rational& operator /= (int d) {
		this->div(Rational(d));
		return *this;
	}

	Rational& operator -(const Rational& rational) {
		this->neg();
		return *this;
	}

	Rational operator-() const { Rational r(this->numerator_, this->denominator_); r.neg(); return r; }
	Rational operator+() const { Rational r(this->numerator_, this->denominator_);          return r; }

private:
	int numerator_;
	int denominator_;
};

Rational operator + (Rational r1, Rational const& r2) {
	return r1 += r2;
}

Rational operator - (Rational r1, Rational const& r2) {
	return r1 -= r2;
}

Rational operator * (Rational r1, Rational const& r2) {
	return r1 *= r2;
}

Rational operator / (Rational r1, Rational const& r2) {
	return r1 /= r2;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
	Rational r = lhs - rhs;
	return *(int*)(&(r)) == 0;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
	Rational r = lhs - rhs;
	return *(int*)(&r) < 0;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
	return !(lhs < rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
	return !(rhs < lhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
	return rhs < lhs;
}



int main() {
	Rational r1(5);
	Rational r2(5);

	if (r1 >= r2) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}

}
