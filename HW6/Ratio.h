#ifndef RATIO_H_INCLUDED
#define RATIO_H_INCLUDED
#include <vector>
#include <ostream>
class Ratio{
	public:
		Ratio() = delete;
		explicit Ratio(long numerator, long denominator= 1);
		explicit Ratio(int numerator, int denominator = 1);
		Ratio(const Ratio &);
		~Ratio() = default;
		Ratio &operator=(const Ratio &);
		long numerator() const;
		void numerator(const long &);
		long denominator() const;
		void denominator(const long &);
		long double ratio() const;
		Ratio subtract(const Ratio &) const;
		Ratio multiply(const Ratio &) const;
		Ratio divide(const Ratio &) const;
		int compare(const Ratio &) const;
		int compare(const long double &) const;
		long gcd(long a, long b) const;
		long lcm(long a, long b) const;
		std::vector<long> tests(const long numer,const  long deno);
		Ratio add(const Ratio &q, const Ratio w = Ratio(0,1), const Ratio e = Ratio(0,1), const Ratio r = Ratio(0,1), const Ratio t = Ratio(0,1), const Ratio y = Ratio(0,1), const Ratio u = Ratio(0,1), const Ratio i = Ratio(0,1)) const;
		Ratio addRatio(const Ratio &) const;
		Ratio setBoth(const long numer, const long deno) const;
		Ratio operator+(const long i) const;
		Ratio operator+(const Ratio&) const;
		Ratio operator-(const long i) const;
		Ratio operator-(const Ratio&) const;
		Ratio operator*(const long i) const;
		Ratio operator*(const Ratio&) const;
		Ratio operator/(const long i) const;
		Ratio operator/(const Ratio&) const;
		void operator+=(const Ratio&);
		void operator+=(const long);
		void operator-=(const Ratio&);
		void operator-=(const long);
		void operator*=(const Ratio&);
		void operator*=(const long);
		void operator/=(const Ratio&);
		void operator/=(const long);
		bool operator==(const Ratio&) const;
		bool operator==(const long double) const;
		bool operator!=(const Ratio&) const;
                bool operator!=(const long double) const;
		bool operator<(const Ratio&) const;
                bool operator<(const long double) const;
		bool operator<=(const Ratio&) const;
                bool operator<=(const long double) const;
		bool operator>(const Ratio&) const;
                bool operator>(const long double) const;
		bool operator>=(const Ratio&) const;
                bool operator>=(const long double) const;
	private:
		long num;
		long denom;	
};

std::ostream &operator<<(std::ostream &, const Ratio &);
std::istream &operator>>(std::istream &, Ratio &);
bool operator==(long double,const Ratio&);
bool operator!=(long double,const Ratio&);
bool operator<(long double,const Ratio&);
bool operator<=(long double,const Ratio&);
bool operator>(long double,const Ratio&);
bool operator>=(long double,const Ratio&);
void operator+=(long double,const Ratio&);
void operator-=(long double,const Ratio&);
void operator*=(long double,const Ratio&);
void operator/=(long double,const Ratio&);
long double operator+(long double, const Ratio&);
long double operator-(long double, const Ratio&);
long double operator*(long double, const Ratio&);
long double operator/(long double, const Ratio&);
#endif /*RATIO_H_INCLUDED */

