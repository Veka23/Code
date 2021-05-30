#include "rtos.hpp"         // for Rtos
#include "event.hpp"        // for Event
#include "rccregisters.hpp" // for RCC
#include "gpioaregisters.hpp"  //for Gpioa
#include "gpiocregisters.hpp"  //for Gpioc
#include "adc1registers.hpp" //for ADC1
#include "susudefs.hpp"
#include "thread.hpp"
#include "nvicregisters.hpp"   //for NVIC
//Vetka VariableTask
#include "VariableTask.hpp"
#include "ADC.hpp" //for ADC
#include "adccommonregisters.hpp" //for ADCCommon
#include "IVariable.hpp"
#include "Voltage.hpp"
//Vetka LedTask
#include "LedTask.hpp"
#include "Led.hpp"
#include "PWM.hpp"
#include "BlueToothTask.hpp"//for BlueToothTask
std::uint32_t SystemCoreClock = 16'000'000U;
 constexpr std::uint32_t UartSpeed4800 = std::uint32_t(16000000U / 9600U);
extern "C" {
int __low_level_init(void)
{
  //Switch on external 16 MHz oscillator
  RCC::CR::HSION::On::Set();
  while (RCC::CR::HSIRDY::NotReady::IsSet())
  {
 
  }
  //Switch system clock on external oscillator
  RCC::CFGR::SW::Hsi::Set();
  while (!RCC::CFGR::SWS::Hsi::IsSet())
  {

  }
  
  RCC::APB2ENR::SYSCFGEN::Enable::Set(); 
  
  //taktirovan'e
  RCC::CR::HSEON::On::Set();
  RCC::CFGR::SW::Hse::Set();
  RCC::APB1ENR::TIM3EN::Enable::Set();
  RCC::APB2ENR::ADC1EN::Enable::Set(); //tekt na adc
  ADC_Common::CCR::TSVREFE::Enable::Set();
  RCC::AHB1ENR::DMA2EN::Enable::Set(); //takt na dma2
  RCC::AHB1ENR::GPIOCEN::Enable::Set();// takt na port C
  RCC::AHB1ENR::GPIOAEN::Enable::Set();// takt na port A
  GPIOA::MODER::MODER0::Analog::Set(); //port A0 yctanovlen v analogovyy rezim
  GPIOC::MODER::MODER8::Alternate::Set(); //port C8 yctanovlen v alternativniy rezim
  GPIOC::AFRH::AFRH8::Af2::Set(); //ckacali chto tyt TIM3_3Kanal
  // Settings PWM
  TIM3::CCER::CC3E::Value1::Set(); //yctanovka registra zaxvata
  // inverst PWM
  TIM3::CCMR2_Output::OC3M::Value6::Set();// PWM rezim
  TIM3::CCMR2_Output::OC3PE::Value1::Set();//registr predvaritel'noj zagruzki 
  TIM3::CR1::ARPE::Value1::Set(); //Vklyuchenie predvaritel'noj zagruzki s avtomaticheskoj perezagruzkoj
  // Run TIM3
  TIM3::CR1::CEN::Value1::Set(); //zapusk tajmera 
  //data for TIM3 CCR
  
  RCC::APB1ENRPack< //podali taktirovanie na timer
  RCC::APB1ENR::TIM2EN::Enable, 
  RCC::APB1ENR::USART2EN::Enable
  >::Set() ;
  
  GPIOA::MODERPack<
    GPIOA::MODER::MODER2::Alternate, // Uart2 TX
    GPIOA::MODER::MODER3::Alternate  // Uart2 RX
    >::Set() ;
  
  GPIOA::AFRLPack <
    GPIOA::AFRL::AFRL2::Af7, // Uart2 TX
    GPIOA::AFRL::AFRL3::Af7  // Uart2 RX
    >::Set() ;
  
    USART2::BRR::Write(UartSpeed4800); //zapicivaem znachenie ckorosti
    USART2::CR1::UE::Enable::Set(); //USART vkluchit'
    NVIC::ISER1::Write(1<<6); //global'noe preryvanie

  return 1;
}
}

Event event(1000ms, 1);
using myADC = ADC<ADC1>;
VariableTask<myADC> myVariableTask(event); //cozdali ob'ekt
LedTask<myVariableTask> myLedTask;
BlueToothTask<myVariableTask> blueToothTask;

int main()
{ 
  using namespace OsWrapper;
  Rtos::CreateThread(myVariableTask, "Execute", ThreadPriority::normal); // cozdaem zadaci dly Rtos
  Rtos::CreateThread(myLedTask, "Execute", ThreadPriority::normal);
  Rtos::CreateThread(blueToothTask, "Execute", ThreadPriority::normal); 
  Rtos::Start();
  return 0;
}