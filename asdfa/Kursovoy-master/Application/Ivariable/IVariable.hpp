#pragma once
#include <array>

class IVariable
{
protected:
  float Value;
  const float k;
  const float b;
 
public:
  IVariable( float k1, float b1): k(k1), b(b1) {}; //cozdaem metod i peredaem k i b
  
  virtual void Calculation(std::uint32_t code) = 0; //racchitivaem znachenie napryzeniy
  
  virtual float GetValue() = 0;
    
  virtual void GetValueAndName() = 0;
  
};