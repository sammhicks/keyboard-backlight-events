#pragma once

#include "common.hpp"

const Color color = Color::Red;
const Colors leftColor = {color, color, Color::Black};
const Colors rightColor = {Color::Black, color, color};
const Brightness brightness = Brightness::Max;
const milliseconds duration = milliseconds(500);
const int count = 4;

int main(int argc, char *argv[]);
