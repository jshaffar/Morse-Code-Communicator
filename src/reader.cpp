//
// Created by jerem on 4/25/2020.
//

#include "mylibrary/reader.h"

#include <cinder/app/App.h>

#include <exception>

#include "../cmake-build-debug/_deps/nlohmann_json-src/single_include/nlohmann/json.hpp"

using std::ifstream;
using std::string;
using std::vector;

Reader::Reader(const string& input) { ReadCommand(input); }

std::vector<std::string> Reader::GetWords() { return this->words_; }

void Reader::ReadCommand(const std::string& command) {
  ifstream file(command);
  if (!file.fail()) {
    if (command.size() > 3 && command.substr(command.size() - 1) == "json") {
      ParseJsonFile(&this->words_, &file, command);
    } else {
      ParseTextFile(&this->words_, &file);
    }
  } else {
    try {
      if (command.size() > 5 &&
          command.substr(command.size() - 5, command.size()) == ".json" &&
          command.find(' ') != string::npos) {
        auto asset = cinder::app::loadAsset(
            command.substr(command.find_last_of(' ') + 1));
        ifstream file(asset->getFilePath());
        string requested_word = command.substr(0, command.find_last_of(' '));
        ParseJsonFile(&this->words_, &file, requested_word);
      } else {
        auto asset = cinder::app::loadAsset(command);
        ifstream file(asset->getFilePath());
        ParseTextFile(&this->words_, &file);
      }

    } catch (std::exception exception) {
      ParseLine(&this->words_, command);
    }
  }
}

void Reader::ParseLine(vector<string>* words_vector, const string& words) {
  // code mostly borrowed from
  // http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html
  if (words.empty()) {
    return;
  } else {
    char delim = ' ';
    std::size_t current, previous = 0;
    current = words.find(delim);
    while (current != std::string::npos) {
      words_vector->push_back(words.substr(previous, current - previous));
      previous = current + 1;
      current = words.find(delim, previous);
    }
    words_vector->push_back(words.substr(previous, current - previous));
  }
}

void Reader::ParseTextFile(vector<std::string>* words_vector,
                           std::ifstream* file) {
  string line;
  while (std::getline(*file, line)) {
    vector<string> words_in_line;
    ParseLine(&words_in_line, line);
    for (const string& word : words_in_line) {
      words_vector->push_back(word);
    }
  }
}

// handles external lib requirment
void Reader::ParseJsonFile(vector<std::string>* words_vector, ifstream* file,
                           const string& requested_word) {
  vector<string> requested_values = vector<string>();
  nlohmann::json text = nlohmann::json::parse(*file);

  if (text.count(requested_word) != 0) {  // key could be found
    words_vector->push_back(text.find(requested_word)->dump());
  } else {  // key couldn't be found
    ParseTextFile(words_vector, file);
  }
}
