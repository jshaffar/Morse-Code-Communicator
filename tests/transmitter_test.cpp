//
// Created by jerem on 5/7/2020.
//

#include "mylibrary/transmitter.h"
#include "mylibrary/morsecode.h"
#include <catch2/catch.hpp>
#include <iostream>

// difficult to test cuz its based on timing, but this is close

TEST_CASE("Check IsOn") {
  MorseCode morse_code = MorseCode(10, 2000, 2000, 2000);
  Transmitter transmitter(morse_code);
  SECTION("Before") {
    REQUIRE(!transmitter.IsOn());
    REQUIRE(!transmitter.IsCurrentlyTransmitting());
  }
  transmitter.Say("e");
  SECTION("During") {
    REQUIRE(transmitter.IsOn());
    REQUIRE(transmitter.IsCurrentlyTransmitting());
  }

  // an alternative to sleep, because I can't figure out how that works
  for (int i = 0; i < 10000000; ++i) {
    std::cout << "waiting" << std::endl;
  }
  SECTION("After") {
    REQUIRE(!transmitter.IsOn());
    REQUIRE(!transmitter.IsCurrentlyTransmitting());
  }
}