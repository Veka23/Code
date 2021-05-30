#pragma once
#include "gpiocregisters.hpp"
#include "rccregisters.hpp"
#include "tim3registers.hpp"

template <typename Timer> // obyavlaem Timer iz drygogog faila
class PWM
{
public: 
  void SetDuty(uint16_t DutyCycle) // cosdaem i peredaem v metod SetDuty
  { 
    Timer::CCR3::Write(DutyCycle); // zapizivaem v register CCR3(register zaxvata i sravniniya) 
  }
};