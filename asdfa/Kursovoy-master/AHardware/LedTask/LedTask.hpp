#pragma once
#include "thread.hpp"
#include "VariableTask.hpp"
#include "Led.hpp"

template <auto& Variabletask> // v LedTask dolzen peredavatcy VariableTask
class LedTask : public OsWrapper::Thread<128> //nasledyem Thread 
{
private:
  float Value;
  Led led1; //cozdali ob'ekt tipa Led i nazvali led1
public:
  void Execute() override //virtyalnyy metod
  {
    for( ; ; )
    {
    Value = Variabletask.GetVolt(); //zapizivaem znachenie napryazeniy v peremenyy Value
    Sleep(100ms); //zaderzka(Rtos)
    led1.CalculateDutyCycle(Value); //vyzivaem metod i peredali znachenie napryzeniy
    led1.SetDutyCycle(); 
    }
  }
};