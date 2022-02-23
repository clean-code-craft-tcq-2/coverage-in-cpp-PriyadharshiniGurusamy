#pragma once
#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#include "typewise-alertTypes.h"

class TemperatureAlert
{
public:
   TemperatureAlert();
   ~TemperatureAlert() {}
   /*Member functions*/
   
   void initializeTemperatureLimits();
   void initializeAlertType();
   
   BreachType inferBreach(double value, TempBoundary tempBoundary);
   void sendAlert(BreachType breachType, AlertTarget alertTarget);
   
   void checkAndAlert(
     AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
   
   void sendToController(BreachType breachType);
   void sendToEmail(BreachType breachType);
   
   /*Member variables*/
   TempLimitMap _tempLimitMap;
   AlertTargetMap _alertTargetMap;
};

#endif
