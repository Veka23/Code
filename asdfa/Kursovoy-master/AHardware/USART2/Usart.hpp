#pragma once
#include "usart2registers.hpp" //for usart2registers
#include "usartdriver.hpp" //for USARTDriver
template<typename TUSARTReg>

class Usart
{
  
  public: 
  Usart(ITransmit& aITransmit): iTransmit(aITransmit) //hranit ssylku na ob"ekt klassa iTransmit.
    {
      
    }
    
   static void WriteByte(std::uint8_t byte) // zapisyvaet dannye v registr DR.
  {
    TUSARTReg::DR::Write(byte);
  }
  
    void InterruptHandler() //proveryaet flagi: Pust li registr dannyh i razresheno li preryvanie po peredache. Zatem vyzyvaet metod OnNextByteTransmit() interfejsa iTransmit
  {
    if(TUSARTReg::SR::TXE::DataRegisterEmpty::IsSet() &&  TUSARTReg::CR1::TXEIE::InterruptWhenTXE::IsSet())
    {
      iTransmit.OnNextByteTransmit();
    }   
    
  }

   static void TransmitEnable() // vklyuchayut peredachu danny
  {
    TUSARTReg::CR1::TE::Enable::Set();
      
  }
  
   static void InterruptEnable() //razreshayut preryvaniya po peredach
  {
    TUSARTReg::CR1::TXEIE::InterruptWhenTXE::Set();      
  }
  
   static void InterruptDisable() // zapreshchayut peredachu danny
  {
    TUSARTReg::CR1::TXEIE::InterruptInhibited::Set();
      
  }
  
   static void TransmitDisable() // vyklyuchayutperedachu danny
  {
    TUSARTReg::CR1::RE::Disable::Set();
  }
private:
  ITransmit& iTransmit;

};