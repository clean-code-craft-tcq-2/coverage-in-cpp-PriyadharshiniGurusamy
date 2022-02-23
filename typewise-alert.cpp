#include "typewise-alert.h"
#include <stdio.h>

TemperatureAlert::TemperatureAlert()
{    
  initializeTemperatureLimits();
  initializeAlertType();
}

void TemperatureAlert::initializeTemperatureLimits()
{
    _tempLimitMap.insert(std::make_pair(PASSIVE_COOLING,std::make_pair(0,35)));
    _tempLimitMap.insert(std::make_pair(HI_ACTIVE_COOLING,std::make_pair(0,45)));
    _tempLimitMap.insert(std::make_pair(MED_ACTIVE_COOLING,std::make_pair(0,40)));
}

void TemperatureAlert::initializeAlertType()
{
    _alertTargetMap.insert(std::make_pair(TO_CONTROLLER, &TemperatureAlert::sendToController));
    _alertTargetMap.insert(std::make_pair(TO_EMAIL, &TemperatureAlert::sendToEmail));
}

void TemperatureAlert::initializeAlertMessage()
{
    _alertMessageMap.insert(std::make_pair(TOO_LOW, "Hi, the temperature is too low"));
    _alertMessageMap.insert(std::make_pair(TOO_HIGH, "Hi, the temperature is too high"));
    _alertMessageMap.insert(std::make_pair(TOO_HIGH, "Hi, the temperature is normal"));
}

template <typename T, typename U>
bool getValuefromKey(std::map<T,U> x, T y , U* z)
{
    bool retVal = false;
    typename std::map<T,U>::iterator itr = x.find(y);
    if(itr != x.end() )
    {
        *z = itr->second;
        retVal = true;
    }
    return retVal;
}

BreachType TemperatureAlert::inferBreach(double value, TempBoundary tempBoundary) 
{
  BreachType retBreachType = NORMAL;
  if(value < tempBoundary.first) {
    retBreachType = TOO_LOW;
  }
  else if(value > tempBoundary.second) {
    retBreachType = TOO_HIGH;
  }
  return retBreachType;
}

void TemperatureAlert::checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{ 
  TempBoundary tempBoundary;
  if ( getValuefromKey(_tempLimitMap, batteryChar.coolingType, &tempBoundary))
  {
     BreachType breachType = inferBreach(temperatureInC , tempBoundary);
     sendAlert(breachType,alertTarget);
  }
}

void TemperatureAlert::sendAlert(BreachType breachType, AlertTarget alertTarget)
{
  void TemperatureAlert::* alertFunction;
  if(getValuefromKey(_alertTargetMap, alertTarget, alertFunction))
  {
     (this->*getValuefromKey(_alertTargetMap, alertTarget))(breachType);
  }
}

void TemperatureAlert::sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void TemperatureAlert::sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  const char* message = "";
  if( getValuefromKey(_alertMessageMap, breachType, message))
  {
     printAlert(recepient , message);
  }
}

void TemperatureAlert::printAlert(const char* recepient , const char* message)
{
     printf("To: %s\n", recepient);
     printf("%s\n", message);
}
