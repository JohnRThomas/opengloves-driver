#pragma once
#include <array>
#include <string>
#include "ForceFeedback.h"

struct VRCommData_t {
    VRCommData_t(std::array<float, 5> flexion, std::array<float, 5> splay, float joyX, float joyY, bool joyButton, bool trgButton, bool aButton, bool bButton, bool grab, bool pinch, bool menu, bool calibrate) :
        flexion(flexion),
        splay(splay),
        joyX(joyX),
        joyY(joyY),
        joyButton(joyButton),
        trgButton(trgButton),
        aButton(aButton),
        bButton(bButton),
        grab(grab),
        pinch(pinch),
        menu(menu),
        calibrate(calibrate){};


    std::array<float, 5> flexion;
    std::array<float, 5> splay;
    float joyX;
    float joyY;
    bool joyButton;
    bool trgButton;
    bool aButton;
    bool bButton;
    bool grab;
    bool pinch;
    bool menu;
    bool calibrate;
};

class IEncodingManager {
 public:
  virtual VRCommData_t Decode(std::string input) = 0;
  virtual std::string Encode(const VRFFBData_t& data) = 0;
  virtual ~IEncodingManager(){};

 private:
  float m_maxAnalogValue = 0.0;
};

template <typename... Args>
std::string string_format(const std::string& format, Args... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;  // Extra space for '\0'
  if (size_s <= 0) {
    DriverLog("Error decoding string");
    return "";
  }
  auto size = static_cast<size_t>(size_s);
  auto buf = std::make_unique<char[]>(size);
  std::snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1);  // We don't want the '\0' inside
}
