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

TEST_CASE("checks initialization") {
  TemperatureAlert obj;
  TempBoundary tempBoundary;
  CHECK(getValuefromKey(obj._tempLimitMap, PASSIVE_COOLING, &tempBoundary));
  CHECK(getValuefromKey(obj._tempLimitMap, HI_ACTIVE_COOLING, &tempBoundary));
  CHECK(getValuefromKey(obj._tempLimitMap, MED_ACTIVE_COOLING, &tempBoundary));
  CHECK_FALSE(getValuefromKey(obj._tempLimitMap, 4, &tempBoundary));
}
