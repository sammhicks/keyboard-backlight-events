#include "power.hpp"

int main(int argc, char *argv[]) {
  SavedKeyboardState savedState;

  setColors(color);
  setBrightness(brightness);
  setState(State::On);

  sleep_for(duration);
}
