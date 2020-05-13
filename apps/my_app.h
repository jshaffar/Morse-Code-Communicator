// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/constants.h>
#include <mylibrary/transmitter.h>
#include <mylibrary/receiver.h>
#include <cinder/audio/Voice.h>
#include <vector>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  ~MyApp() override;
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  Constants constant_;
  bool in_menu_mode_;
  bool in_transmitter_mode_;
  bool in_receiver_mode_;
  bool is_on_;
  std::string input_;
  std::vector<std::string> coded_words_;
  std::vector<std::string> uncoded_words;
  std::vector<std::chrono::milliseconds>* time_point_changes_;
  bool did_start_;
  bool started_transmitting_;

  Code* code_;
  Transmitter transmitter_;
  Receiver receiver_;
  cinder::audio::VoiceRef sound_;
  bool is_finished_;
  std::string finished_message_;

  void SetUpTransmitterMode();
  void SetUpReceiverMode();
  void DecodeReceiver();
  void DrawMenuUI() const;
  void DrawTransmitterUI() const;
  void DrawReceiverUI();
  void DrawFinishedUI();
  template <typename C>
  void PrintText(const std::string& text, const C& color, const cinder::ivec2& size,
      const cinder::vec2& loc, const float font_size_ = 100) const;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
