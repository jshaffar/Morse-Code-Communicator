//
// Created by jerem on 5/6/2020.
//

#include "mylibrary/reader.h"

#include <../apps/my_app.h>

#include <catch2/catch.hpp>

TEST_CASE("Non file expression") {
  SECTION("empty") {
    Reader reader("");
    REQUIRE(reader.GetWords().empty());
  }
  SECTION("one word") {
    Reader reader("stunt");
    REQUIRE(reader.GetWords()[0] == "stunt");
  }
  SECTION("Sentence") {
    Reader reader("Harry Potter and the sorcerors stone");
    REQUIRE(reader.GetWords()[0] == "Harry");
    REQUIRE(reader.GetWords()[3] == "the");
    REQUIRE(reader.GetWords()[5] == "stone");
  }
}

TEST_CASE("File expression") {
  SECTION("Valid File") {
    Reader reader("preamble.txt");
    REQUIRE(reader.GetWords()[0] == "We");
    REQUIRE(reader.GetWords()[1] == "the");
    REQUIRE(reader.GetWords()[8] == "Order");
    int size = reader.GetWords().size();
    REQUIRE(reader.GetWords()[size - 1] == "America.");
  }
  SECTION("Invalid File") {
    Reader reader("nonexistantfile.txt");
    REQUIRE(reader.GetWords()[0] == "nonexistantfile.txt");
  }
}

TEST_CASE("Json expression") {
  SECTION("valid key") {
    Reader reader("pi basicjson.json");
    REQUIRE(reader.GetWords()[0] == "3.141");
  }
  SECTION("invalid key") {
    Reader reader("iDontExist basicjson.txt");
    REQUIRE(reader.GetWords()[0] == "iDontExist");
  }
}
