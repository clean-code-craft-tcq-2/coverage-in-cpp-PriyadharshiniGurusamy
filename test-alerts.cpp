#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "typewise-alertTypes.h"

TEST_CASE("infers the breach according to limits") {
  TemperatureAlert obj;
  REQUIRE(obj.inferBreach(12, std::make_pair(20, 30)) == TOO_LOW);
}
