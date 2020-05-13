//
// Created by jerem on 4/27/2020.
//

#include "mylibrary/transmitter.h"

#include <chrono>
#include <iostream>

#include "mylibrary/constants.h"

using std::string;
using std::vector;
using std::chrono::system_clock;

Transmitter::Transmitter() {}

Transmitter::Transmitter(const Code& code) {
  this->code_values_ = code.code_;
  this->interval_between_symbols_ = Constants::interval_between_symbols;
}

bool Transmitter::IsOn() const {
  if (this->timestamps_.empty()) {  // transmitter hasn't started yet
    return false;
  }

  auto current_time = system_clock::now();
  for (int index = 1; index < this->timestamps_.size(); ++index) {
    if (current_time < this->timestamps_[index].first) {
      // if the current time is in between 2 timestampts, it will return whether
      // the next timestamp is mapped at on or off
      return this->timestamps_[index - 1].second;
    }
  }
  return false;
}

bool Transmitter::IsCurrentlyTransmitting() const {
  if (this->timestamps_.empty()) {
    return false;
  } else if (this->timestamps_.at(this->timestamps_.size() - 1).first <
             system_clock::now()) {
    return false;
  } else {
    return true;
  }
}

void Transmitter::Say(const string& code_word) {
  system_clock::time_point time_point;

  if (this->timestamps_.empty()) {  // user has no words loaded up in queue
    time_point = system_clock::now();
  } else {
    // user has words loaded up, so word should start at the end of previous
    // word + a space
    time_point = this->timestamps_[this->timestamps_.size() - 1].first;
    +std::chrono::milliseconds(this->code_values_.at(' '));
  }

  for (char symbol : code_word) {
    if (symbol == ' ') {
      // the spaces get messed up unless done this way
      time_point += std::chrono::milliseconds(this->code_values_.at(' '));
      continue;
    }

    // time_point increases from last point by the interval between the symbols
    // and then again by the duration of the symbol. These 2 points represet a
    // full on and off
    time_point += std::chrono::milliseconds(this->interval_between_symbols_);
    this->timestamps_.emplace_back(time_point, true);
    time_point += std::chrono::milliseconds(this->code_values_.at(symbol));
    this->timestamps_.emplace_back(time_point, false);
  }
}

void Transmitter::Say(const vector<string>& code_words) {
  this->timestamps_.clear();
  string text;
  for (const string& word : code_words) {
    text += word;
    text += "  ";
  }
  Say(text);
}
