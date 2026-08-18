#pragma once
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <cstdint>
class Rational{
public:
 Rational(int64_t n=0,int64_t d=1):num_(n),den_(d){Normalize();}
 int64_t GetNumerator()const{return num_;}
 int64_t GetDenominator()const{return den_;}
 Rational& operator+=(const Rational& r){num_=num_*r.den_+r.num_*den_;den_*=r.den_;Normalize();return *this;}
 Rational& operator-=(const Rational& r){num_=num_*r.den_-r.num_*den_;den_*=r.den_;Normalize();return *this;}
 Rational& operator*=(const Rational& r){num_*=r.num_;den_*=r.den_;Normalize();return *this;}
 Rational& operator/=(const Rational& r){num_*=r.den_;den_*=r.num_;Normalize();return *this;}
 Rational operator-()const{return {-num_,den_};}
 explicit operator double()const{return static_cast<double>(num_)/den_;}
private:
 void Normalize(){if(den_==0)throw std::invalid_argument("zero denominator");if(den_<0){num_=-num_;den_=-den_;}auto g=std::gcd(num_,den_);num_/=g;den_/=g;}
 int64_t num_,den_;
};
inline Rational operator+(Rational a,const Rational&b){return a+=b;}
inline Rational operator-(Rational a,const Rational&b){return a-=b;}
inline Rational operator*(Rational a,const Rational&b){return a*=b;}
inline Rational operator/(Rational a,const Rational&b){return a/=b;}
inline bool operator==(const Rational&a,const Rational&b){return a.GetNumerator()==b.GetNumerator()&&a.GetDenominator()==b.GetDenominator();}
inline bool operator!=(const Rational&a,const Rational&b){return !(a==b);}
inline bool operator<(const Rational&a,const Rational&b){return a.GetNumerator()*b.GetDenominator()<b.GetNumerator()*a.GetDenominator();}
inline bool operator>(const Rational&a,const Rational&b){return b<a;}
inline std::ostream& operator<<(std::ostream&out,const Rational&r){out<<r.GetNumerator();if(r.GetDenominator()!=1)out<<" / "<<r.GetDenominator();return out;}
inline std::istream& operator>>(std::istream&in,Rational&r){int64_t n=0,d=1;in>>n;if(in.peek()=='/'){in.get();in>>d;}else{in>>std::ws;if(in.peek()=='/'){in.get();in>>d;}}r=Rational(n,d);return in;}
