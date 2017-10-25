#include "low-battery.hpp"

int main(int argc, char *argv[]) {
  SavedKeyboardState savedState;

  setColors(leftColor);
  setBrightness(brightness);
  setState(State::On);

  for (int i = 0; i < count; ++i) {
    setColors(leftColor);

    sleep_for(duration);

    setColors(rightColor);

    sleep_for(duration);
  }
}
