#include "tape.h"
#include <stdexcept>

using namespace AutomataLab;

Tape::Tape(QString input) {
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == BLANK_CHARACTER)
      throw std::runtime_error("Tape cannot contain blank character (#)");
    tape.push_back(input[i]);
  }
  currentIndex = 0;
}

QChar Tape::read() { return tape[currentIndex]; }

void Tape::moveRight() {
  currentIndex++;
  if (currentIndex >= tape.size())
    tape.push_back(BLANK_CHARACTER);
}

void Tape::moveLeft() {
  if (currentIndex == 0) {
    tape.push_front(BLANK_CHARACTER);
  } else {
    currentIndex--;
  }
}

QString Tape::toString() {
  QString string = "";
  for (auto character : tape) {
    string += character;
  }
  return string;
}

void Tape::write(QChar character) { tape[currentIndex] = character; }
