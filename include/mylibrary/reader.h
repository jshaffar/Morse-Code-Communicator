//
// Created by jerem on 4/25/2020.
//

#ifndef FINALPROJECT_READER_H
#define FINALPROJECT_READER_H

#include <fstream>
#include <iostream>
#include <vector>

#include "code.h"

/**
 * This class is for reading in the command line arguement
 * It also handles the external library of nholmann json
 */
class Reader {
 public:
  /**
   * Takes a command, called in my_app with the command that the user types in
   * The input can contain 3 possibilities:
   * 1) The command is an english expression
   * 2) The command has a file endpoint and wants youto read to a file
   * 3) The command has a string followed by a .json file and wants you to only
   * handle the object that has the expression as a key ex. "hello world.json"
   * would try to return the words of the first string it can find in world.json
   * with the key hello
   * @param input A user inputted command
   */
  explicit Reader(const std::string& input);

  /**
   * @return vector of words the user processed. See constructor for what it
   * will be
   */
  std::vector<std::string> GetWords();

 private:
  std::vector<std::string> words_;
  void ReadCommand(const std::string& command);
  void ParseLine(std::vector<std::string>* words_vector,
                 const std::string& words);
  void ParseTextFile(std::vector<std::string>* words_vector,
                     std::ifstream* file);
  void ParseJsonFile(std::vector<std::string>* words_vector,
                     std::ifstream* file, const std::string& requested_word);
};

#endif  // FINALPROJECT_READER_H
