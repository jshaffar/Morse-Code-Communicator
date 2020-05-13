//
// Created by jerem on 4/30/2020.
//

#ifndef FINALPROJECT_RECEIVER_H
#define FINALPROJECT_RECEIVER_H

#include <cinder/Camera.h>
#include <mylibrary/code.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "cinder/Capture.h"
#include "cinder/audio/Buffer.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/InputNode.h"
#include "cinder/audio/MonitorNode.h"
#include "cinder/audio/Node.h"

/**
 * This class tries to hear a code and react to it. It has 2 mode: on and off,
 * depending on whether its hearing an alarm or not
 */
class Receiver {
 public:
  /**
   * An object that detects if the external volume is substanially larger than normal.
   * Its constantly called in my_app.cpp in receiver mode and when its on detects
   * and is used to detect if the user is producing a sound for the code at that
   * specific timestamp
   */
  explicit Receiver();

  /**
   * The primary function of this class, this returns on if the external volume
   * is bigger by a factor of kVolumeSensitivity from constants than the intial
   * volume
   * @return True if on, false otherwise
   */
  bool IsOn();

 private:
  ci::audio::Context* ctx_;
  ci::audio::InputNodeRef input_;
  std::shared_ptr<cinder::audio::MonitorSpectralNode> monitor_spectral_node_;
  float initial_volume_;
  int volume_index_;

  void SetUpMic();
};

#endif  // FINALPROJECT_RECEIVER_H
