#pragma once
//#include "USARTDriver.h"
#include "thread.hpp"//for thread
#include "usartconfig.hpp"
#include <stdio.h> //for sprintf
using namespace OsWrapper;

template<auto& myVariableTask>
class BlueToothTask: public Thread<512>
{
public:

  void Execute() //otvechaet za peredachu znachenij po Bluetooth
  {
    for(;;)
    {
   out = myVariableTask.GetVolt(); //hranit stroku so znacheniem naprazeniy
  
   sprintf(mes, "Voltage: %1.4f V \n" , out);// hranit sformirovannuyu dlya otpravki stroku so znacheniemnapryzeniy
   usartDriver.SendMessage(mes, strlen(mes));
   Sleep(1000ms);
    }
  }
  
private:
  float out;
  char mes[20]; // hranit sformirovannuyu dlya otpravki stroku so znacheniemnapryzeniy
};