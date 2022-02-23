#ifndef ALERT_TYPES_H
#define ALERT_TYPES_H
#include <map>
#include <utility>

class TemperatureAlert;

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

/* Lower limit, Upper Limit*/
typedef std::pair< double,double > TempBoundary;
typedef std::map< CoolingType,TempBoundary > TempLimitMap;
typedef std::map< AlertTarget ,void (TemperatureAlert::*)(BreachType) > AlertTargetMap;

#endif
