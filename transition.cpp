#include "transition.h"

using namespace AutomataLab;

Transition::Transition(State *fromState, std::vector<QChar> acceptedInputs)
    : _fromState(fromState), acceptedInputs(acceptedInputs) {}

Transition::Transition(State *fromState, QChar acceptedInput)
    : _fromState(fromState) {
  acceptedInputs.push_back(acceptedInput);
}

bool Transition::accepts(QChar input) {
  for (auto character : acceptedInputs) {
    if (character == input)
      return true;
  }
  return false;
}

void Transition::setAcceptInputs(std::vector<QChar> acceptInputs) {
  acceptedInputs = acceptInputs;
}

void Transition::setAcceptInput(QChar input) {
  acceptedInputs.clear();
  acceptedInputs.push_back(input);
}

Transition::~Transition() {}

State *Transition::fromState() { return _fromState; }

bool Transition::operator==(Transition &transition) {
  return *(this->fromState()) == *(transition.fromState()) &&
         this->acceptedInputs == transition.acceptedInputs;
}

std::vector<QChar> Transition::acceptInputs() { return acceptedInputs; }
