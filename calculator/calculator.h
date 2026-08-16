#pragma once
#include <string>
#include <optional>
#include <cmath>
#include <type_traits>
#include "rational.h"
#include "pow.h"
using Error=std::string;
template<class Number> class Calculator{
public:
 void Set(Number n){number_=n;} Number GetNumber()const{return number_;}
 std::optional<Error> Add(Number x){number_+=x;return std::nullopt;}
 std::optional<Error> Sub(Number x){number_-=x;return std::nullopt;}
 std::optional<Error> Mul(Number x){number_*=x;return std::nullopt;}
 std::optional<Error> Div(Number x){if constexpr(!std::is_floating_point_v<Number>){if(x==Number{})return Error("Division by zero");}number_/=x;return std::nullopt;}
 std::optional<Error> Pow(Number x){
  if constexpr(!std::is_floating_point_v<Number>){if(number_==Number{}&&x==Number{})return Error("Zero power to zero");}
  if constexpr(std::is_same_v<Number,Rational>){if(x.GetDenominator()!=1)return Error("Fractional power is not supported");number_=::Pow(number_,x);}
  else if constexpr(std::is_integral_v<Number>){if constexpr(std::is_signed_v<Number>){if(x<0)return Error("Integer negative power");}number_=IntegerPow(number_,x);}
  else number_=std::pow(number_,x);
  return std::nullopt;
 }
 void Save(){mem_=number_;} void Load(){if(mem_)number_=*mem_;} void ClearMem(){mem_.reset();} bool GetHasMem()const{return mem_.has_value();}
private:Number number_{};std::optional<Number> mem_;};
