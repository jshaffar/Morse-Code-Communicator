
//
// Created by jerem on 4/23/2020.
//

#ifndef FINALPROJECT_MORSECODE_H
#define FINALPROJECT_MORSECODE_H

#include <iostream>
#include <vector>

#include "code.h"

class MorseCode : public Code {
 public:
  /**
   * Creates a morse code object with 4 different values refering to the 4
   * different timestamps that are possible
   * @param dot_interval Time that a dot represents
   * @param dash_interval Time that a dash represents
   * @param space_interval Time that the space between letters should be,
   * between words is triple
   * @param interval_between_symbol Time between symbols, this is specific to
   * morse code
   */
  explicit MorseCode(int dot_interval = 100, int dash_interval = 200,
                     int space_interval = 300,
                     int interval_between_symbol = 100);

  /**
   * @param words Vector of english words
   * @return Those words converted into the code language
   */
  std::string BuildCode(std::string word) override;

  /**
   * @param word Single english words
   * @return That word converted into the code language
   */
  std::vector<std::string> BuildCode(std::vector<std::string> words) override;

  /**
   * @return The invterval between symbols in the code
   */
  int GetIntervalBetweenSymbols() override;

  /**
   * Takes a series of timestamps and based on which ones are closest to the
   * symbol turns it into the code language
   * @return The best approximation of those timestamps in code language
   */
  std::string ConvertTimestampToCode(
      std::vector<std::chrono::milliseconds>*) override;

  /**
   * @param text A string in code language
   * @return A string that corresponds with text in human language
   */
  std::string ConvertCodeToWords(const std::string& text) override;

  /**
   * Returns whether code reads those specific charecters
   * @param c Any char in ASCI
   * @return whether this code reads that specific error
   */
  bool IsAllowedCharacter(const char& c) override;

  /**
   * Takes a character and translates it to its morse code expression, static
   * for convenience
   * @param c A charecter
   * @return Its morse code equivelent
   */
  static std::string ConvertLetterToMorse(char& c);

  /**
   * Converts a given word to morse code
   * @param word Any string (if it doesn't have appriate values won't touch
   * those specific values)
   * @return Its morse code equivelent with a single space representing the
   * change between words
   */
  static std::string ConvertWordToMorse(std::string& word);

  /**
   * @param morse A word in morse code format
   * @return The given charecter that word is associated with
   */
  static char ConvertMorseToLetter(const std::string& morse);

  /**
   * @param words A vector of words in english
   * @return A vector of those words in morse code
   */
  static std::vector<std::string> GetWordsInMorse(
      std::vector<std::string>& words);

 private:
  int interval_between_symbols_;
};

#endif  // FINALPROJECT_MORSECODE_H
