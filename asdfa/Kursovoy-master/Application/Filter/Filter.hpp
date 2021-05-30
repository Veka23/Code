#pragma once
#include <cmath> 

class Filter
{
  private:
    
  float OldValue = 0.0f; //obyavlzem peremenyy
  static constexpr float dt = 100.0f;
  static constexpr float RC = 100.0f;
  inline static const float tay = 1.0f - exp(-dt/RC);
    
  public:
  float Update(float Value)//cozdali klass i peredaem v nego znachenie napryzeniy
  {
    float FilteredValue = OldValue + (Value - OldValue)*tay; 
    OldValue = FilteredValue;
    return FilteredValue;
  }
  
  float GetOldValue (float Value)
  {
    float FilteredValue = OldValue + (Value - OldValue)*tay;
    OldValue = FilteredValue;
    return FilteredValue;
  }
};