#include <map>
#include <utility>

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
typedef map< CoolingType,TempBoundary > TempLimitMap;
typedef map< AlertTarget ,void (*)(BreachType) > AlertTargetMap;
