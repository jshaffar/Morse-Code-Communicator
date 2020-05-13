//
// Created by jerem on 5/6/2020.
//

#include <mylibrary/morsecode.h>

#include <catch2/catch.hpp>

using std::string;

MorseCode morse_code_ = MorseCode();

TEST_CASE("Build Code") {
  // this should cover convertwordtomorse as its basically the nonstatic version
  // of it. Should also cover convertmorsetoletter, as it runs a loop of that
  SECTION("Empty") { REQUIRE(morse_code_.BuildCode("") == ""); }
  SECTION("One Letter") { REQUIRE(morse_code_.BuildCode("a") == ".-"); }
  SECTION("One Word") {
    REQUIRE(morse_code_.BuildCode("fake") == "..-. .- -.- .");
  }
  SECTION("Sentence") {
    string sentence = ("cinder is atrocious");
    REQUIRE(morse_code_.BuildCode(sentence) ==
            ("-.-. .. -. -.. . .-.  .. ...  .- - .-. --- -.-. .. --- ..- ..."));
  }
  SECTION("Capitals") {
    string sentence = "OK";
    REQUIRE(morse_code_.BuildCode(sentence) == ("--- -.-"));
  }
  SECTION("Numbers") {
    string sentence = "69420";
    string s = morse_code_.BuildCode(sentence);
    REQUIRE(morse_code_.BuildCode(sentence) == "-.... ----. ....- ..--- -----");
  }
}

TEST_CASE("Is allowed character") {
  SECTION("Lower case") { REQUIRE(morse_code_.IsAllowedCharacter('a')); }
  SECTION("Upper case") { REQUIRE(morse_code_.IsAllowedCharacter('A')); }
  SECTION("Number") { REQUIRE(morse_code_.IsAllowedCharacter('1')); }
  SECTION("Symbol") { REQUIRE(morse_code_.IsAllowedCharacter('/')); }
  SECTION("Invalid Character") {
    // question marks are reserved for charecters that can't be parsed
    REQUIRE(morse_code_.IsAllowedCharacter('?'));
  }
}
