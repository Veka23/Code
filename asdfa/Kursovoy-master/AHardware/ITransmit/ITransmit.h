#pragma once
#include "usartdriver.hpp" //for USARTDriver
class ITransmit
{
public: 
  virtual void OnNextByteTransmit() = 0; //dostup klassu Usart k metodu OnNextByteTransmit() klassa USARTDriver
};