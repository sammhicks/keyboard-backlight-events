#pragma once

#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

using std::array;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::istream;
using std::ifstream;
using std::ostream;
using std::ofstream;
using std::string;
using std::ostringstream;
using std::range_error;
using std::this_thread::sleep_for;

const string moduleDirectory = "/sys/devices/platform/clevo_xsm_wmi/";

const string statePath = moduleDirectory + "kb_state";
const string brightnessPath = moduleDirectory + "kb_brightness";
const string modePath = moduleDirectory + "kb_mode";
const string colorPath = moduleDirectory + "kb_color";

enum class State : bool { Off = 0, On = 1 };

enum class Brightness { Min = 0, Max = 10 };

enum class Mode { Random, Custom, Breathe, Cycle, Wave, Dance, Tempo, Flash };

enum class Color { Black, Blue, Red, Magenta, Green, Cyan, Yellow, White };

struct Colors {
  Color left, middle, right;
};

const array<const string, 8> colorStrings = {
    "black", "blue", "red", "magenta", "green", "cyan", "yellow", "white"};

int getInt(const string &path);
void setInt(const string &path, int value);

State getState();
void setState(State state);

Brightness getBrightness();
void setBrightness(Brightness brightness);

Mode getMode();
void setMode(Mode mode);

const string &colorString(Color color);
Color colorString(const string &str);

Color getColor(istream &is);
void setColor(ostream &os, Color color);

Colors getColors();
void setColors(Color color);
void setColors(const Colors &colors);

struct KeyboardState {
  State state;
  Brightness brightness;
  Mode mode;
  Colors colors;
};

KeyboardState getKeyboardState();
void setKeyboardState(const KeyboardState &keyboardState);

class SavedKeyboardState {
private:
  KeyboardState keyboardState;

  SavedKeyboardState(const SavedKeyboardState &other) = delete;
  SavedKeyboardState &operator=(const SavedKeyboardState &) = delete;

public:
  SavedKeyboardState();
  ~SavedKeyboardState();
};
