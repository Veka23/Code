#pragma once
#include "Filter.hpp"
#include <array>
#include "IVariable.hpp"

class Voltage : public IVariable
{
public:
  using IVariable::IVariable; //obyvlayet compilytory chto mi budem icpolzovat' ob'ekt IVariable iz prostranstva imen IVariable
  void Calculation(std::uint32_t code) override //opisivaem metod iz IVariable
  {
    Value = k*code + b;
  }
  
   float GetValue() override
  {
    return Value;
  }
  
  void GetValueAndName() override
  {}
};