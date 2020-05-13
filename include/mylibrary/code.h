//
// Created by jerem on 4/28/2020.
//

#ifndef FINALPROJECT_CODE_H
#define FINALPROJECT_CODE_H

#include <chrono>
#include <iostream>
#include <map>
#include <vector>

/**
 * This class is the code that the 2 computers use to communicate. Extend from
 * this class to use this code.
 */
class Code {
 public:
  /**
   * A map of characters of the code to the amount of miliseconds that that
   * value requires
   */
  std::map<char, int> code_;

  /**
   * @param words Vector of english words
   * @return Those words converted into the code language
   */
  virtual std::vector<std::string> BuildCode(
      std::vector<std::string> words) = 0;

  /**
   * @param word Single english words
   * @return That word converted into the code language
   */
  virtual std::string BuildCode(std::string word) = 0;

  /**
   * @return The invterval between symbols in the code
   */
  virtual int GetIntervalBetweenSymbols() = 0;

  /**
   * Takes a series of timestamps and based on which ones are closest to the
   * symbol turns it into the code language
   * @return The best approximation of those timestamps in code language
   */
  virtual std::string ConvertTimestampToCode(
      std::vector<std::chrono::milliseconds>*) = 0;

  /**
   * @param text A string in code language
   * @return A string that corresponds with text in human language
   */
  virtual std::string ConvertCodeToWords(const std::string& text) = 0;

  /**
   * Returns whether code reads those specific characters
   * @param c Any char in ASCI
   * @return whether this code reads that specific error
   */
  virtual bool IsAllowedCharacter(const char& c) = 0;
};
#endif  // FINALPROJECT_CODE_H
