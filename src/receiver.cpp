//
// Created by jerem on 4/30/2020.
//

#include "mylibrary/receiver.h"
#include "mylibrary/constants.h"
#include <fstream>


using namespace ci;

using std::chrono::system_clock;

// For a tutorial on sound through cinder go to
// https://libcinder.org/docs/guides/audio/index.html

Receiver::Receiver() { SetUpMic(); }

bool Receiver::IsOn() {
  auto volume = this->monitor_spectral_node_->getVolume();

  // the mic takes a couple milliseconds to spin up and starts up at 0,
  // so this step is needed
  ++volume_index_;
  if (this->volume_index_ == 100) {
    this->initial_volume_ = volume;
  }

  if (this->initial_volume_ == 0) {
    return false;
  } else {
    return volume >
           this->initial_volume_ * Constants::kVolumeSensitivityMultiplier;
  }
}

void Receiver::SetUpMic() {
  this->ctx_ = audio::Context::master();
  this->ctx_->enable();
  this->input_ = this->ctx_->createInputDeviceNode();
  auto monitorFormat =
      audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024);
  this->monitor_spectral_node_ =
      this->ctx_->makeNode(new audio::MonitorSpectralNode(monitorFormat));
  this->input_ >> this->monitor_spectral_node_;
  this->input_->enable();
  std::string s = ci::audio::Device::printDevicesToString();
  this->initial_volume_ = 0;
  this->volume_index_ = 0;
}
