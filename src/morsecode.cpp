//
// Created by jerem on 4/23/2020.
//

#include "mylibrary/morsecode.h"
#include "mylibrary/constants.h"
#include <cmath>
#include <vector>

using std::string;
using std::vector;
using std::chrono::milliseconds;

MorseCode::MorseCode(int dot_interval, int dash_interval, int space_interval,
                     int interval_between_symbols) {
  this->code_.insert(std::pair<char, int>('.', dot_interval));
  this->code_.insert(std::pair<char, int>('-', dash_interval));
  this->code_.insert(std::pair<char, int>(' ', space_interval));
  this->interval_between_symbols_ = interval_between_symbols;
}

string MorseCode::BuildCode(string word) { return ConvertWordToMorse(word); }

vector<string> MorseCode::BuildCode(vector<string> words) {
  return GetWordsInMorse(words);
}

string MorseCode::ConvertTimestampToCode(vector<milliseconds> *timestamps) {
  string text;
  for (int index = 1; index < timestamps->size(); index = index + 2) {
    // every other timestamp is an off switch so this goes through and tries to
    // differentiate the letters.
    long duration =
        timestamps->at(index).count() - timestamps->at(index - 1).count();

    if (duration < Constants::kTimeSensitivityMultiplier) {
      continue;
    }
    int min_dur;
    char min_char;
    for (auto it = this->code_.begin(); it != this->code_.end(); ++it) {
      long diff = abs(duration - it->second);
      if (it == this->code_.begin() || diff < min_dur) {
        min_char = it->first;
        min_dur = diff;
      }
    }
    text += min_char;
    // then it goes through the even timestamps which are all spaces and decides
    // whether its a space of the letter or the word or between different symbols
    // in the morse code
    if (index != timestamps->size() - 1) {
      long space_duration =
          timestamps->at(index + 1).count() - timestamps->at(index).count();
      long between_symbol_diff =
          abs(space_duration - this->interval_between_symbols_);
      long between_spaces_diff = abs(space_duration - this->code_.at(' '));
      if (between_symbol_diff <= between_spaces_diff) {
        continue;  // this means that there is no change in letter
      } else {
        int spaces = space_duration / this->code_.at(' ');
        for (int space_number = 0; space_number < spaces; ++space_number) {
          text += ' ';
        }
      }
    }
  }
  return text;
}

string MorseCode::ConvertCodeToWords(const string &text) {
  vector<string> morse_letters = vector<string>();
  string word = "";

  for (char c : text) {
    if (c == ' ') {      // theres a space
      if (word == "") {  // no word currently exists so we should add a space
        morse_letters.emplace_back(" ");
      } else {
        morse_letters.push_back(
            word);  // the word was completed so should now be reset
        word = "";
      }
    } else {
      word += c;  // word is continuing
    }
  }

  morse_letters.push_back(word);
  string output_text;
  for (const string &morse_letter : morse_letters) {
    output_text += ConvertMorseToLetter(morse_letter);
  }
  return output_text;
}

std::string MorseCode::ConvertWordToMorse(std::string &word) {
  string morse_word;
  for (int index = 0; index < word.size(); ++index) {
    morse_word += MorseCode::ConvertLetterToMorse(word[index]);
    if (index != word.size() - 1) {
      morse_word += ' ';
    }
  }
  return morse_word;
}

vector<string> MorseCode::GetWordsInMorse(vector<string> &words) {
  vector<string> morse_words;
  morse_words.reserve(words.size());
  for (string &word : words) {
    morse_words.push_back(ConvertWordToMorse(word));
  }
  return morse_words;
}

int MorseCode::GetIntervalBetweenSymbols() {
  return this->interval_between_symbols_;
}

bool MorseCode::IsAllowedCharacter(const char &c) {
  char to_check = c;
  if (ConvertLetterToMorse(to_check) != "?") {
    return true;
  }
}

// Converting methods, put on bottom to improve readability
string MorseCode::ConvertLetterToMorse(char &c) {
  if (c >= 'A' &&
      c <= 'Z') {  // there's no upper case letters in traditional morse code
    c += ('a' - 'A');
  }
  // values from https://morsecode.world/international/morse.html
  switch (c) {
    case 'a':
      return ".-";  //".-"
    case 'b':
      return "-...";
    case 'c':
      return "-.-.";
    case 'd':
      return "-..";
    case 'e':
      return ".";
    case 'f':
      return "..-.";
    case 'g':
      return "--.";
    case 'h':
      return "....";
    case 'i':
      return "..";
    case 'j':
      return ".---";
    case 'k':
      return "-.-";
    case 'l':
      return ".-..";
    case 'm':
      return "--";
    case 'n':
      return "-.";
    case 'o':
      return "---";
    case 'p':
      return ".--.";
    case 'q':
      return "--.-";
    case 'r':
      return ".-.";
    case 's':
      return "...";
    case 't':
      return "-";
    case 'u':
      return "..-";
    case 'v':
      return "...-";
    case 'w':
      return ".--";
    case 'x':
      return "-..-";
    case 'y':
      return "-.--";
    case 'z':
      return "--..";
    case '1':
      return ".----";
    case '2':
      return "..---";
    case '3':
      return "...--";
    case '4':
      return "....-";
    case '5':
      return ".....";
    case '6':
      return "-....";
    case '7':
      return "--...";
    case '8':
      return "---..";
    case '9':
      return "----.";
    case '0':
      return "-----";
    case '&':
      return ".-..-";
    case '@':
      return ".--.-.";
    case ')':
      return "-.--.-";
    case '(':
      return "-.--.";
    case ':':
      return "---..-";
    case ',':
      return "--..--";
    case '=':
      return "-...-";
    case '!':
      return "-.-.--";
    case '.':
      return ".-.-.-";
    case '-':
      return "-....-";
    case '+':
      return ".-.-.";
    case '/':
      return "-..-.";
    case ' ':
      return "";
    default:
      return "";
  }
}

char MorseCode::ConvertMorseToLetter(const std::string &morse) {
  // switch statements don't work for some reason
  if (morse == ".-") {
    return 'a';
  } else if (morse == "-...") {
    return 'b';
  } else if (morse == "-.-.") {
    return 'c';
  } else if (morse == "-..") {
    return 'd';
  } else if (morse == ".") {
    return 'e';
  } else if (morse == "..-.") {
    return 'f';
  } else if (morse == "--.") {
    return 'g';
  } else if (morse == "....") {
    return 'h';
  } else if (morse == "..") {
    return 'i';
  } else if (morse == ".---") {
    return 'j';
  } else if (morse == "-.-") {
    return 'k';
  } else if (morse == ".-..") {
    return 'l';
  } else if (morse == "--") {
    return 'm';
  } else if (morse == "-.") {
    return 'n';
  } else if (morse == "---") {
    return 'o';
  } else if (morse == ".--.") {
    return 'p';
  } else if (morse == "--.-") {
    return 'q';
  } else if (morse == ".-.") {
    return 'r';
  } else if (morse == "...") {
    return 's';
  } else if (morse == "-") {
    return 't';
  } else if (morse == "..-") {
    return 'u';
  } else if (morse == "...-") {
    return 'v';
  } else if (morse == ".--") {
    return 'w';
  } else if (morse == "-..-") {
    return 'x';
  } else if (morse == "-.--") {
    return 'y';
  } else if (morse == "--..") {
    return 'z';
  } else if (morse == " ") {
    return ' ';
  } else if (morse == ".----") {
    return '1';
  } else if (morse == "..---") {
    return '2';
  } else if (morse == "...--") {
    return '3';
  } else if (morse == "....-") {
    return '4';
  } else if (morse == ".....") {
    return '5';
  } else if (morse == "-....") {
    return '6';
  } else if (morse == "--...") {
    return '7';
  } else if (morse == "---..") {
    return '8';
  } else if (morse == "----.") {
    return '9';
  } else if (morse == "-----") {
    return '0';
  } else if (morse == ".-..-") {
    return '&';
  } else if (morse == ".--.-.") {
    return '@';
  } else if (morse == "-.--.-") {
    return ')';
  } else if (morse == "-.--.") {
    return '(';
  } else if (morse == "---...") {
    return ':';
  } else if (morse == "--..--") {
    return ',';
  } else if (morse == "-...-") {
    return '=';
  } else if (morse == "-...-") {
    return '!';
  } else if (morse == ".-.-.-") {
    return '.';
  } else if (morse == "-....-") {
    return '-';
  } else if (morse == ".-.-.") {
    return '+';
  } else if (morse == "-..-.") {
    return '/';
  } else {
    return '?';  // this is when the letter could not be recognized
  }
}
