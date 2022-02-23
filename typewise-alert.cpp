#include "typewise-alert.h"
#include <stdio.h>

void TemperatureAlert::TemperatureAlert()
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
    _alertTargetMap.insert(std::make_pair(TO_CONTROLLER, &sendToController));
    _alertTargetMap.insert(std::make_pair(TO_EMAIL, &sendToEmail));
}

template <typename T, typename U>
U getValuefromKey(std::map<T,U> x, T y)
{
    U value;
    typename std::map<T,U>::iterator itr = x.find(y);
    if(itr != x.end() )
    {
        value = itr->second;
    }
    return value;
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
  BreachType breachType = inferBreach(temperatureInC , getValuefromKey(_tempLimitMap,batteryChar.coolingType));
  sendAlert(breachType,alertTarget);
}

void TemperatureAlert::sendAlert(BreachType breachType, AlertTarget alertTarget)
{
  getValuefromKey(_alertTargetMap, alertTarget)(breachType);
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void TemperatureAlert::sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
