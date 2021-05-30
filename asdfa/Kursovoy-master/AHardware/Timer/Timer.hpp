#pragma once
#include "rccregisters.hpp"
#include "tim2registers.hpp"
#include "nvicregisters.hpp"
class Timer
{
  public:

    void Start()
    {
      RCC::APB1ENR::TIM2EN::Enable::Set();
      TIM2::PSC::Write(7999U);
      TIM2::ARR::Write(19999);
      TIM2::CNT::Write(0U);
      NVIC::ISER0::Write(1U << 28U);
      TIM2::DIER::UIE::Enable::Set();
      TIM2::SR::UIF::NoInterruptPending::Set();
      TIM2::CR1::CEN::Enable::Set();
      TIM2::CR1::URS::OverflowEvent::Set();
    }
private:
  uint32_t Period;
};