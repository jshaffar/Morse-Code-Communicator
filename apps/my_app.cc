// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/Text.h>
#include <cinder/gl/gl.h>
#include <mylibrary/morsecode.h>
#include <mylibrary/writer.h>

#include "mylibrary/reader.h"

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;

using std::rand;
using std::string;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

namespace myapp {

MyApp::MyApp() {}

void MyApp::setup() {
  cinder::gl::clear();
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  this->in_menu_mode_ = true;
  this->in_transmitter_mode_ = false;
  this->in_receiver_mode_ = false;
  this->is_on_ = false;
  this->time_point_changes_ = new std::vector<milliseconds>();
  this->input_ = "";
  this->did_start_ = false;
  this->started_transmitting_ = false;
  this->code_ = new MorseCode(
      this->constant_.dot_interval, this->constant_.dash_interval,
      this->constant_.space_interval,
      this->constant_
          .interval_between_symbols);  // add the time values here if needed.
  // sound from
  // https://www.e2s.com/references-and-guidelines/listen-and-download-alarm-tones
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(MyApp::loadAsset("sound.wav"));
  this->sound_ = cinder::audio::Voice::create(sourceFile);
  this->is_finished_ = false;
}

void MyApp::update() {
  if (this->in_transmitter_mode_ &&
      !this->transmitter_.IsCurrentlyTransmitting() &&
      !this->started_transmitting_) {
    this->transmitter_.Say(this->coded_words_);
    this->started_transmitting_ = true;
  }
  if (this->in_transmitter_mode_ &&
      !this->transmitter_.IsCurrentlyTransmitting() && this->did_start_ &&
      !this->is_finished_) {  // transmitter done talking
    this->is_finished_ = true;
    this->sound_->stop();
    this->finished_message_ += "Done transmitting message " + this->input_;
  }
}

void MyApp::draw() {
  // cinder::gl::enableAlphaBlending();
  if (this->in_menu_mode_) {
    DrawMenuUI();
  } else if (this->in_transmitter_mode_ && !this->is_finished_ &&
             this->transmitter_.IsCurrentlyTransmitting()) {
    DrawTransmitterUI();
  } else if (this->in_receiver_mode_ && !this->is_finished_) {
    DrawReceiverUI();
  } else if (this->is_finished_) {
    DrawFinishedUI();
  }
}

void MyApp::keyDown(KeyEvent event) {
  auto key = event.getChar();

  if (this->in_menu_mode_) {
    if (key == '\r') {  // enter key should set up and enter light mode
      if (event.isControlDown()) {
        SetUpReceiverMode();
      } else {
        SetUpTransmitterMode();
      }
      this->did_start_ = true;
    } else if (key == KeyEvent::KEY_BACKSPACE) {
      if (this->input_.size() != 0) {
        this->input_.pop_back();
      }
    } else if (this->code_->IsAllowedCharacter(key)) {
      this->input_ += key;
    }
  } else if (!this->is_finished_) {
    if (key == '\r') {
      if (this->in_receiver_mode_) {
        DecodeReceiver();
      } else if (this->in_transmitter_mode_) {
        this->finished_message_ +=
            "Transmitter ended early. Transmitted following message: " +
            this->input_;
      }
      this->is_finished_ = true;
      this->sound_->stop();
    }
  }
}

void MyApp::SetUpTransmitterMode() {
  this->in_menu_mode_ = false;
  this->in_transmitter_mode_ = true;
  Reader reader(this->input_);
  this->uncoded_words = reader.GetWords();
  this->coded_words_ = this->code_->BuildCode(this->uncoded_words);
  this->transmitter_ = Transmitter(*this->code_);
  this->sound_->start();
}

void MyApp::SetUpReceiverMode() {
  this->in_menu_mode_ = false;
  this->in_receiver_mode_ = true;
  Reader reader(this->input_);
  this->receiver_ = Receiver();
}

void MyApp::DecodeReceiver() {
  string raw_code =
      this->code_->ConvertTimestampToCode(this->time_point_changes_);
  string text = this->code_->ConvertCodeToWords(raw_code);
  if (this->input_.empty()) {
    this->finished_message_ += text;

  } else {
    bool did_write = Writer::WriteToFile(this->input_, text);
    this->finished_message_ = text;

  }
}

void MyApp::DrawMenuUI() const {
  cinder::gl::clear(ColorA(1, 0, 1, .5));
  const cinder::ivec2 size = {getWindowWidth(), getWindowHeight() * .3f};
  const cinder::vec2 center = getWindowCenter();
  const Color text_color = Color::black();
  PrintText(constant_.kProjectName, text_color, size,
            {center.x, getWindowHeight() * .1}, getWindowWidth() * .1);
  PrintText(this->constant_.kMenuMessage, text_color, size,
            {center.x, getWindowHeight() * .3}, getWindowWidth() * .05);
  PrintText(this->input_, Color::gray(.5f), size,
            {center.x, getWindowHeight() * .6f}, getWindowWidth() * .05);
}

void MyApp::DrawReceiverUI() {
  if (this->receiver_.IsOn()) {
    if (!this->is_on_) {
      this->time_point_changes_->push_back(
          duration_cast<milliseconds>(system_clock::now().time_since_epoch()));
      this->is_on_ = true;
    }
    cinder::gl::clear(Color::white());

  } else if (!this->receiver_.IsOn()) {
    if (this->is_on_) {
      this->time_point_changes_->push_back(
          duration_cast<milliseconds>(system_clock::now().time_since_epoch()));
      this->is_on_ = false;
    }
    cinder::gl::clear(Color::black());
  }
}

void MyApp::DrawTransmitterUI() const {
  if (this->transmitter_.IsOn()) {
    cinder::gl::clear(Color::white());
    this->sound_->start();
  } else {
    cinder::gl::clear(Color::black());
    this->sound_->stop();
  }
  const cinder::ivec2 size = {getWindowWidth(), getWindowHeight() * .3};
  const cinder::vec2 center = getWindowCenter();
}

void MyApp::DrawFinishedUI() {
  cinder::gl::clear(ColorA(.4f, .2f, .6f, .9f));
  const cinder::ivec2 size = {getWindowWidth(), getWindowHeight() * .3};
  const cinder::vec2 center = getWindowCenter();
  PrintText(this->finished_message_, ColorA(.0, .0, .9, .8), size,
            {center.x, getWindowHeight() * .6f}, getWindowWidth() * .05f);
}

template <typename C>
void MyApp::PrintText(const string& text, const C& color,
                      const cinder::ivec2& size, const cinder::vec2& loc,
                      const float fontSize) const {
  cinder::gl::color(color);

  auto box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(cinder::Font(constant_.kPrimaryFont, fontSize))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

MyApp::~MyApp() {
  delete this->code_;
  delete this->time_point_changes_;
}

}  // namespace myapp
