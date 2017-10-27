#include "common.hpp"

int getInt(const string &path) {
  ifstream ifs(path);

  int value;

  ifs >> value;

  return value;
}

void setInt(const string &path, int value) {
  ofstream ofs(path);

  ofs << value;
}

State getState() { return static_cast<State>(getInt(statePath)); }
void setState(State state) { setInt(statePath, static_cast<int>(state)); }

Brightness getBrightness() {
  return static_cast<Brightness>(getInt(brightnessPath));
}
void setBrightness(Brightness brightness) {
  setInt(brightnessPath, static_cast<int>(brightness));
}

Mode getMode() { return static_cast<Mode>(getInt(modePath)); }
void setMode(Mode mode) { setInt(modePath, static_cast<int>(mode)); }

const string &colorString(Color color) {
  return colorStrings[static_cast<int>(color)];
}

Color colorString(const string &str) {
  for (size_t i = 0; i < colorStrings.size(); ++i) {
    if (str == colorStrings[i]) {
      return static_cast<Color>(i);
    }
  }

  throw range_error("Invalid color");
}

Color getColor(istream &is) {
  string str;

  is >> str;

  return colorString(str);
}

void setColor(ostream &os, Color color) { os << colorString(color); }

Colors getColors() {
  ifstream ifs(colorPath);

  Colors colors;

  colors.left = getColor(ifs);
  colors.middle = getColor(ifs);
  colors.right = getColor(ifs);

  return colors;
}

void setColors(Color color) {
  ofstream ofs(colorPath);
  setColor(ofs, color);
}

void setColors(const Colors &colors) {
  ofstream ofs(colorPath);

  setColor(ofs, colors.left);
  ofs << " ";
  setColor(ofs, colors.middle);
  ofs << " ";
  setColor(ofs, colors.right);
}

KeyboardState getKeyboardState() {
  return {getState(), getBrightness(), getMode(), getColors()};
}

void setKeyboardColorMode(const KeyboardState &keyboardState) {
  switch (keyboardState.mode) {
  case Mode::Custom:
  case Mode::Breathe:
    setColors(keyboardState.colors);
  default:
    break;
  }

  setMode(keyboardState.mode);
}

void setKeyboardState(const KeyboardState &keyboardState) {
  if (keyboardState.state == State::On) {
    setKeyboardColorMode(keyboardState);
    setState(State::On);
  } else {
    setState(State::Off);
    setKeyboardColorMode(keyboardState);
  }
  setBrightness(keyboardState.brightness);
}

SavedKeyboardState::SavedKeyboardState() : keyboardState(getKeyboardState()) {}

SavedKeyboardState::~SavedKeyboardState() { setKeyboardState(keyboardState); }
