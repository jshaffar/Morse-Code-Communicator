//
// Created by jerem on 5/5/2020.
//

#ifndef FINALPROJECT_WRITER_H
#define FINALPROJECT_WRITER_H

#include <iostream>
#include <fstream>

/**
 * Quick one method class to make writing to files easy
 */
class Writer {
 public:
  static bool WriteToFile(const std::string& file_name, const std::string& text);
};

#endif  // FINALPROJECT_WRITER_H
