#include "tape.h"
#include <stdexcept>

using namespace AutomataLab;

Tape::Tape(QString input) {
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == BLANK_CHARACTER)
      throw std::runtime_error("Tape cannot contain blank character (#)");
    tape.push_back(input[i]);
  }
  _currentIndex = 0;
  _inputSize = input.size();
}

QChar Tape::read() { return tape[_currentIndex]; }

void Tape::moveRight() {
  _currentIndex++;
  if (_currentIndex >= tape.size())
    tape.push_back(BLANK_CHARACTER);
}

void Tape::moveLeft() {
  if (_currentIndex == 0) {
    tape.push_front(BLANK_CHARACTER);
  } else {
    _currentIndex--;
  }
}

unsigned int Tape::currentIndex() { return _currentIndex; }

QString Tape::toString() {
  QString string = "";
  for (auto character : tape) {
    string += character;
  }
  return string;
}

unsigned int Tape::inputSize() const { return _inputSize; }

void Tape::write(QChar character) { tape[_currentIndex] = character; }
