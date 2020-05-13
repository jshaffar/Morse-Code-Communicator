//
// Created by jerem on 4/24/2020.
//

#ifndef FINALPROJECT_CONSTANTS_H
#define FINALPROJECT_CONSTANTS_H

#include <cinder/gl/draw.h>

#include <iostream>

struct Constants {
 public:
  /**
   * Name of app
   */
  const std::string kProjectName = "Unbreakable";

  /**
   * Name of font
   */
  const std::string kPrimaryFont = "Arial";

  /**
   * Message for user on menu screen
   */
  const std::string kMenuMessage =
      "Welcome! Type in a word, file, or key and json "
      "file. Press enter for transmitter mode and ctrl enter for receiver mode";
  
  /**
   * Sensitivity of microphone to changes in volume
   * Tradeoff is larger sensitivity requires louder sound
   * but is less likely to make mistakes from extraneous
   * noise
   */
  constexpr static float kVolumeSensitivityMultiplier = 6.0f;

  /**
   * Sensitivity of microphone to quick changes. Larger value
   * will decrease prob of quick movement messing it up,
   * but requires larger spaces
   */
  constexpr static int kTimeSensitivityMultiplier = 100;

  /**
   * Values for how long you want transmission to be.
   * {500,2000,1000,300} definitely works, but experimenting
   * needs to be done, and different values excepcially for
   * the spaces may get messed up values if too short, too
   * close to each other, or to clsoe to the time sensitivity
   * multiplier
   */
  const static int dot_interval = 500;
  const static int dash_interval = 2000;
  const static int space_interval = 1000;
  const static int interval_between_symbols = 300;
};

#endif  // FINALPROJECT_CONSTANTS_H
