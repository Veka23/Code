#pragma once
#include "Voltage.hpp"
#include "thread.hpp"
#include "event.hpp"
#include "IVariable.hpp"
#include "ADC.hpp"
#include "DMA.hpp"
#include "Filter.hpp"
#include <iostream> 

template <typename myADC> 
class VariableTask : public OsWrapper::Thread<512>
{
private:
  Filter filter;
  Voltage VoltageValue = Voltage((3.3F/4096), 0); //peredaem znachenie v klass IVariable i fikciryem v peremenyy VoltageValue
  OsWrapper::Event& myEvent; // ccylka na event
  float VoltValue = 0.0F;
public:
  
  void Execute() override
  {
    myADC::adcConfig(Resolution::Bits12, tSampleRate::Cycles480); //nastraivaem adc
    myADC::SetChannels(18); //podkluchaem kanali
    myADC::dmaConfig(); //podkluchaem DMA
    myADC::On(); //vkluchaen adc
    myADC::Start();
       
   for( ; ;)
  {
    auto codes = myADC::GetValue(); //zapicivaem znachenie napryzeniy v codes
    VoltageValue.Calculation(codes[0]); //raschtivaem znachenie 
    VoltageValue.GetValueAndName();
    auto var = filter.Update(VoltageValue.GetValue()); // zapicivaem v peremennyy var znacheniy napryzeniy c primineniem filtra
    std::cout<<var<<std::endl;
    Sleep(100ms);
  } 
  }
  
  float GetVolt()
  {
    return filter.Update(VoltageValue.GetValue());
  }
  
  VariableTask(OsWrapper::Event& event): myEvent(event)
  {}
};