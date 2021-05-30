#pragma once
#include "dma2registers.hpp"

template<class D>
class DMA
{
public:
  
  static void ChannelSet() 
  {
    D::S0CR::CHSEL::Value0::Set(); 
  }
  
  static void DirectionSet() //Ustanavlivaem napravlemie 
  {
    D::S0CR::DIR::Value0::Set();
  }
  
  static void DataSizeSet() //Ustanavlivaem ob'emi pamati periferii i pamaty
  {
    D::S0NDTR::NDT::Set(2); //kolichectvo elementov dannyx dly peredaci
    D::S0CR::MSIZE::Value2::Set(); //rasmer dannyx v pamyti
    D::S0CR::MINC::Value1::Set(); //rezim uvelicheniy pamati
    D::S0CR::PSIZE::Value2::Set(); //razmer perefiriynyx dannix
    D::S0CR::PINC::Value0::Set(); //periferiynyi rezim prirasheniya
  }
  
  static void TargetSet(uint32_t PeriAdrr, uint32_t Pcode) //Ustanabvimaem oblast pamati gde budut schitannie znachenia
  {
    D::S0PAR::Set(PeriAdrr); //zapizivaem adres registra pereviriynyx dannix
    D::S0CR::CT::Value0::Set(); //ykasivaem zelevyy oblast' dannyx dly 1 peredachi
    D::S0M0AR::Set(Pcode); //yctanovka bazovogo adreca dannix v kotoryy budet zapicivatcy i chitivatcy dannye
  }
  
  static void StreamOn()  //Vkluchaen CircularMode, zapuskaem potok
  {
    D::S0CR::CIRC::Value1::Set(); //yctanovka ziklicheskogo rezima DMA
    D::S0CR::EN::Value1::Set(); //vklychenie potoka
  }
};