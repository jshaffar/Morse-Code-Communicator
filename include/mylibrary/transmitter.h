//
// Created by jerem on 4/27/2020.
//

#ifndef FINALPROJECT_TRANSMITTER_H
#define FINALPROJECT_TRANSMITTER_H

#include <chrono>
#include <iostream>
#include <map>
#include <vector>

#include "code.h"

/**
 * This class is the one who talks in the code.
 */
class Transmitter {
 public:
  /**
   * Intializes empty transmitter
   */
  explicit Transmitter();

  /**
   * Intializes transmitter with given code. Doesn't start until the Say()
   * method is called externally, but initializes the transmitter
   * @param code The code language used in the project
   */
  explicit Transmitter(const Code& code);

  /**
   * Says the word in the transmitters code language. Note that by saying, I
   * mean there's a vector of timestamps that's developed from this function.
   * IsOn(), which is called in my_app.cc takes care of whether that timestamp
   * is when the user is talking or not
   * @param code_word A word in code language
   */
  void Say(const std::string& code_word);

  /**
   * See above but with spaces in between all of the words in the vector
   * @param code_words
   */
  void Say(const std::vector<std::string>& code_words);

  /**
   * This function returns whether the transmitter is talking or resting at
   * the time it's called. If the transmitter has never been called, will return
   * false as well
   * @return Whether the transmitter is on at the millisecond it
   * was called
   */
  bool IsOn() const;

  /**
   * Returns whether transmitter was ever intialized. Will only return true if
   * both user has called say on a transmitter, and their are still letters left
   * that the transmitter hasn't said yet
   * @return Whether transmitter is currently transmitting
   */
  bool IsCurrentlyTransmitting() const;

 private:
  std::map<char, int> code_values_;
  std::vector<std::pair<std::chrono::system_clock::time_point, bool>>
      timestamps_;
  int interval_between_symbols_;
};

#endif  // FINALPROJECT_TRANSMITTER_H
