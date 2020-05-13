//
// Created by jerem on 5/5/2020.
//

#include "mylibrary/writer.h"

using std::string;
using std::ofstream;

bool Writer::WriteToFile(const string& file_name, const string& text) {
  ofstream file(file_name);
  if (file.fail()) {
    return false;
  } else {
    for (const char& c : text) {
      file << c;
    }
    file.close();
    return true;
  }
}
