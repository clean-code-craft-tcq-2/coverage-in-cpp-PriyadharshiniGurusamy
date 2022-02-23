#pragma once
#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#include "typewise-alertTypes.h"


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

class TemperatureAlert
{
public:
   TemperatureAlert();
   ~TemperatureAlert() {}
   /*Member functions*/
   
   void initializeTemperatureLimits();
   void initializeAlertType();
   void initializeAlertMessage();
   
   BreachType inferBreach(double value, TempBoundary tempBoundary);
   void sendAlert(BreachType breachType, AlertTarget alertTarget);
   
   void checkAndAlert(
     AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
   
   void sendToController(BreachType breachType);
   void sendToEmail(BreachType breachType);
   void printAlert(const char* recepient , std::string message);
   
   /*Member variables*/
   TempLimitMap _tempLimitMap;
   AlertTargetMap _alertTargetMap;
   AlertMessageMap _alertMessageMap;
};

#endif
