#include "Ratio.h"
#include <stdexcept>
#include <cmath>
#include <vector>
#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;

Ratio::Ratio(long top, long bottom){
	vector<long> numer_denom = tests(top,bottom);
	num = numer_denom[0];
	denom = numer_denom[1];
}
Ratio::Ratio(int top, int bottom){
	vector<long> numer_denom = tests(top,bottom);
        num = numer_denom[0];
        denom = numer_denom[1];
}


long Ratio::numerator() const{
	return num;
}
void Ratio::numerator(const long &top){
	long bot = this->denom;
	vector<long> numer_denom = tests(top,bot);
	this->num = numer_denom[0];
	this->denom = numer_denom[1];
}
long Ratio::denominator() const{
	return denom;
}
void Ratio::denominator(const long &bottom){
	long top = this->num;
	vector<long> numer_denom = tests(top, bottom);
	this->num = numer_denom[0];
	this->denom = numer_denom[1];
}

vector<long> Ratio::tests(const long numer,const  long deno){
	long new_numer = numer;
	long new_deno = deno;
	if(numer == 0){
		new_deno = 1;
	}
	if(deno < 0){
		new_deno = abs(deno);
		new_numer = numer * -1;
	}
	if(deno == 0){
                throw runtime_error("Denominator equal to 0");
        }
	long divideval = gcd(abs(new_numer),new_deno);
	new_numer = new_numer/divideval;
	new_deno = new_deno/divideval;
	vector<long> numer_denom {new_numer,new_deno};
	return numer_denom;
}
//https://www.geeksforgeeks.org/c-program-find-gcd-hcf-two-numbers/
long Ratio::gcd(long a, long b) const{
    // Everything divides 0  
    if (a == 0) 
       return b; 
    if (b == 0) 
       return a; 
   
    // base case 
    if (a == b) 
        return a; 
   
    // a is greater 
    if (a > b) 
        return gcd(a-b, b); 
    return gcd(a, b-a); 
}
//https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/
long Ratio::lcm(long a, long b) const{  
    return (a*b)/gcd(a, b);  
}
Ratio::Ratio(const Ratio &copy): num(copy.numerator()), denom(copy.denominator()){
}

long double Ratio::ratio() const{
	long double numer = static_cast<long double>(this->num);
	long double deno = static_cast<long double>(this->denom);
	return (numer/deno);
}
Ratio &Ratio::operator=(const Ratio &ratio){
	this->num = ratio.num;
	this->denom = ratio.denom;
	return *this;
}
Ratio Ratio::subtract(const Ratio &sub) const{
	long leastc = lcm(this->denominator(), sub.denominator());
	long mulnum1 = leastc/this->denom;
	long newnumer1 = this->num * mulnum1;
	long mulnum2 = leastc/sub.denom;
	long newnumer2 = sub.num * mulnum2;		
	long numer = newnumer1-newnumer2;
	return Ratio(numer,leastc);
}
Ratio Ratio::multiply(const Ratio &mult) const{
	return Ratio(this->num * mult.num, this->denom * mult.denom);
}
Ratio Ratio::divide(const Ratio &divi) const{
	return Ratio(this->num * divi.denom, this->denom * divi.num);
}
int Ratio::compare(const Ratio &cmp) const{
	double long rat1 = this->ratio();
	double long rat2 = cmp.ratio();
	if(rat1 > rat2){ return 1;}
	else if(rat2 > rat1){ return -1;}
	else {return 0;}
}
int Ratio::compare(const long double &cmp) const{
	double long num1 = this->ratio();
	if(num1 > cmp){ return 1;}
        else if(cmp > num1){ return -1;}
        else {return 0;}
}
Ratio Ratio::addRatio(const Ratio &arg1) const{
	long leastc = lcm(this->denominator(), arg1.denominator());
        long mulnum1 = leastc/this->denom;
        long newnumer1 = this->num * mulnum1;
        long mulnum2 = leastc/arg1.denom;
        long newnumer2 = arg1.num * mulnum2;
        long numer = newnumer1+newnumer2;
        return Ratio(numer,leastc);

}
Ratio Ratio::add(const Ratio &q, const Ratio w, const Ratio e, const Ratio r, const Ratio t, const Ratio y, const Ratio u, const Ratio i) const{
	Ratio n1 = this->addRatio(q);
	Ratio n2 = n1.addRatio(w);
	Ratio n3 = n2.addRatio(e);
	Ratio n4 = n3.addRatio(r);
	Ratio n5 = n4.addRatio(t);
	Ratio n6 = n5.addRatio(y);
	Ratio n7 = n6.addRatio(u);
	return n7.addRatio(i);	
}
Ratio Ratio::setBoth(const long numer, const long deno) const{
	return Ratio(numer, deno);
}
ostream &operator<<(ostream &stream, const Ratio &val) {
	return stream << val.numerator() << '/' << val.denominator();
}
istream &operator>>(istream &stream, Ratio &add){
	string tempString;
	string delim = "/";
	size_t pos = 0;
	string first;
	stream >> tempString;
		while ((pos = tempString.find(delim)) != string::npos) {
 			first = tempString.substr(0, pos);
    			tempString.erase(0, pos + delim.length());
		}
		try{
			long top = stol(first);
			long bottom = stol(tempString);
			Ratio copy(top,bottom);
			add = copy;
		}
		catch(...){}
	
	return stream;
}
Ratio Ratio::operator+(const long int i) const{
	long int bot = 1;
	return this->addRatio(Ratio(i,bot));	
}
Ratio Ratio::operator+(const Ratio &rhs) const{
        return this->addRatio(rhs);
}
Ratio Ratio::operator-(const long int i) const{
        long int bot = 1;
        return this->subtract(Ratio(i,bot));
}
Ratio Ratio::operator-(const Ratio &rhs) const{
        return this->subtract(rhs);
}
Ratio Ratio::operator/(const long int i) const{
        long int bot = 1;
        return this->divide(Ratio(i,bot));
}
Ratio Ratio::operator/(const Ratio &rhs) const{
        return this->divide(rhs);
}
Ratio Ratio::operator*(const long int i) const{
        long int bot = 1;
        return this->multiply(Ratio(i,bot));
}
Ratio Ratio::operator*(const Ratio &rhs) const{
        return this->multiply(rhs);
}
void Ratio::operator+=(const Ratio &rhs){
	*this = this->addRatio(rhs);
}
void Ratio::operator+=(const long i){
	long int bot = 1;
	*this = this->addRatio(Ratio(i,bot));
}
void Ratio::operator-=(const Ratio &rhs){
	*this = this->subtract(rhs);
}
void Ratio::operator-=(const long i){
	long int bot = 1;
	*this = this->subtract(Ratio(i,bot));
}
void Ratio::operator*=(const Ratio &rhs){
	*this = this->multiply(rhs);
}
void Ratio::operator*=(const long i){
	long int bot = 1;
	*this = this->multiply(Ratio(i,bot));
}
void Ratio::operator/=(const Ratio &rhs){
	*this = this->divide(rhs);
}
void Ratio::operator/=(const long i){
	long int bot = 1;
	*this = this->divide(Ratio(i,bot));
}
bool Ratio::operator==(const Ratio &rhs) const{
	if(this->compare(rhs) == 0){
		return true;
	}
	else{return false;}
}
bool Ratio::operator==(const long double i) const{
	if(this->compare(i) == 0){
                return true;
        }
        else{return false;}
}
bool Ratio::operator!=(const Ratio &rhs) const{
	if(this->compare(rhs) != 0){
		return true;
	}
	else{return false;}
}
bool Ratio::operator!=(const long double i) const{
	if(this->compare(i) != 0){
                return true;
        }
        else{return false;}
}
bool Ratio::operator<(const Ratio &rhs) const{
	if(this->compare(rhs) == -1){
		return true;
	}
	else{return false;}
}
bool Ratio::operator<(const long double i) const{
	if(this->compare(i) == -1){
                return true;
        }
        else{return false;}
}
bool Ratio::operator<=(const Ratio &rhs) const{
	if((this->compare(rhs) == -1) || (this->compare(rhs) == 0)){
                return true;
        }
        else{return false;}
}
bool Ratio::operator<=(const long double i) const{
	if((this->compare(i) == -1) || (this->compare(i) == 0)){
                return true;
        }
        else{return false;} 
}
bool Ratio::operator>(const Ratio &rhs) const{
	if(this->compare(rhs) == 1){
		return true;
	}
	else{return false;}
}
bool Ratio::operator>(const long double i) const{
	if(this->compare(i) == 1){
		return true;
	}
	else{return false;};
}
bool Ratio::operator>=(const Ratio &rhs) const{
	if((this->compare(rhs) == 1) || (this->compare(rhs) == 0)){
                return true;
        }
        else{return false;} 
}
bool Ratio::operator>=(const long double i) const{
	if((this->compare(i) == 1) || (this->compare(i) == 0)){
                return true;
        }
        else{return false;} 
}
bool operator<(long double i, const Ratio &rhs){
	return !(rhs > i);
}
bool operator==(long double i,const Ratio &rhs){
	return (rhs==i);
}
bool operator!=(long double i,const Ratio &rhs){
	return(rhs!=i);
}
bool operator<=(long double i,const Ratio &rhs){
	return !(rhs>=i);
}
bool operator>(long double i,const Ratio &rhs){
	return!(rhs<i);
}
bool operator>=(long double i,const Ratio &rhs){
	return!(rhs<=i);
}
void operator+=(long double i,const Ratio &rhs){
	i += rhs.ratio();
}
void operator-=(long double i,const Ratio &rhs){
	i -= rhs.ratio();
}
void operator*=(long double i,const Ratio &rhs){
	i *= rhs.ratio();
}
void operator/=(long double i,const Ratio &rhs){
	i /= rhs.ratio();
}
long double operator+(long double i, const Ratio &rhs){
	return i + rhs.ratio();
}
long double operator-(long double i, const Ratio &rhs){
	return i - rhs.ratio();
}
long double operator*(long double i, const Ratio &rhs){
	return i * rhs.ratio();
}
long double operator/(long double i, const Ratio &rhs){
	return i / rhs.ratio();
}
