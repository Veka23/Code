#pragma once
#include <array>
#include <cassert>

class ITransmit
{
public: 
  virtual void OnNextByteTransmit() = 0;
};

template<typename TUsart>
class USARTDriver
{
public:
  
  
  
   void OnNextByteTransmit() // otvechaet za pobajtovuyu peredachu soobshcheniya
  {
    TUsart::WriteByte(TransmitBuffer[i++]);    
    if (i >= size) 
    {
      TUsart::TransmitDisable();
      TUsart::InterruptDisable();
      i = 0U;
    }
  }
   void SendMessage(const char* message, size_t aSize) //otvechaet za otpravku soobshcheniya po USART
  {
    assert(size <= 255); 
    memcpy(TransmitBuffer.data(), message, aSize);
    size = aSize;
    i = 0U;
    TUsart::WriteByte(TransmitBuffer[i++]); 
    TUsart::TransmitEnable();
    TUsart::InterruptEnable(); 
         
  }

private:
  std::size_t i = 0U; //hranit nomer peredavaemogo elementa stroki
  std::array<std::uint8_t, 255> TransmitBuffer; //hranit znachenie, kotoroe neobhodimo peredat
  size_t size = 0U;  // hranit razmer stroki, kotoruyu neobhodimo peredat
  
};

