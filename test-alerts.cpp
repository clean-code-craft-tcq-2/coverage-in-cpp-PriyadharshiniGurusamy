#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "typewise-alertTypes.h"

TEST_CASE("infers the breach according to limits") {
  TemperatureAlert obj;
  REQUIRE(obj.inferBreach(12, std::make_pair(20, 30)) == TOO_LOW);
  REQUIRE(obj.inferBreach(40, std::make_pair(20, 30)) == TOO_HIGH);
  REQUIRE(obj.inferBreach(25, std::make_pair(20, 30)) == NORMAL);
}

TEST_CASE("checks Alert to Email") {
  TemperatureAlert obj;
  TempBoundary tempBoundary;
  BatteryCharacter batteryCharacter;
  batteryCharacter.coolingType = PASSIVE_COOLING;
  obj.checkAndAlert(TO_EMAIL, batteryCharacter, 12);
  obj.checkAndAlert(TO_EMAIL, batteryCharacter, 40);
  CHECK(getValuefromKey(obj._tempLimitMap, batteryCharacter.coolingType, &tempBoundary));
  
  batteryCharacter.coolingType = HI_ACTIVE_COOLING;
  obj.checkAndAlert(TO_EMAIL, batteryCharacter, 12);
  obj.checkAndAlert(TO_EMAIL, batteryCharacter, 50);
  CHECK(getValuefromKey(obj._tempLimitMap, batteryCharacter.coolingType, &tempBoundary));
  
  batteryCharacter.coolingType = MED_ACTIVE_COOLING;
  obj.checkAndAlert(TO_EMAIL, batteryCharacter, 12);
  obj.checkAndAlert(TO_EMAIL, batteryCharacter, 50);  
  CHECK(getValuefromKey(obj._tempLimitMap, batteryCharacter.coolingType, &tempBoundary));
  
  batteryCharacter.coolingType = static_cast<CoolingType>(4);
  obj.checkAndAlert(TO_EMAIL, batteryCharacter, 12);
  obj.checkAndAlert(TO_EMAIL, batteryCharacter, 50);
  CHECK_FALSE(getValuefromKey(obj._tempLimitMap, batteryCharacter.coolingType, &tempBoundary));
}

TEST_CASE("checks Alert to controller") {
  TemperatureAlert obj;
  TempBoundary tempBoundary;
  BatteryCharacter batteryCharacter;
  batteryCharacter.coolingType = PASSIVE_COOLING;  
  obj.checkAndAlert(TO_CONTROLLER, batteryCharacter, 12);
  obj.checkAndAlert(TO_CONTROLLER, batteryCharacter, 40);
  
  batteryCharacter.coolingType = HI_ACTIVE_COOLING;
  obj.checkAndAlert(TO_CONTROLLER, batteryCharacter, 12);
  obj.checkAndAlert(TO_CONTROLLER, batteryCharacter, 50);
  
  batteryCharacter.coolingType = MED_ACTIVE_COOLING;
  obj.checkAndAlert(TO_CONTROLLER, batteryCharacter, 12);
  obj.checkAndAlert(TO_CONTROLLER, batteryCharacter, 50);
  
  batteryCharacter.coolingType = static_cast<CoolingType>(4);
  obj.checkAndAlert(TO_CONTROLLER, batteryCharacter, 12);
  obj.checkAndAlert(TO_CONTROLLER, batteryCharacter, 50);
}
