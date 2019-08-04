#include "transition.h"

using namespace AutomataLab;

Transition::Transition(State *fromState, State *toState)
    : _fromState(fromState), _toState(toState) {}

Transition::Transition(State *fromState, State *toState,
                       std::vector<QChar> acceptedInputsArg)
    : Transition(fromState, toState) {
  _acceptedInputs = acceptedInputsArg;
}

Transition::Transition(State *fromState, State *toState, QChar acceptedInput)
    : _fromState(fromState), _toState(toState) {
  _acceptedInputs.push_back(acceptedInput);
}

bool Transition::accepts(QChar input) {
  for (auto character : _acceptedInputs) {
    if (character == input)
      return true;
  }
  return false;
}

void Transition::setAcceptInputs(std::vector<QChar> acceptInputs) {
  _acceptedInputs = acceptInputs;
}

void Transition::setAcceptInput(QChar input) {
  // Clearing previous accepted inputs
  _acceptedInputs.clear();
  _acceptedInputs.push_back(input);
}

Transition::~Transition() {}

State *Transition::fromState() { return _fromState; }

State *Transition::toState() { return _toState; }

bool Transition::operator==(Transition &transition) {
  return *(this->fromState()) == *(transition.fromState()) &&
         this->_acceptedInputs == transition._acceptedInputs &&
         *(this->toState()) == *(transition.toState());
}

void Transition::writeJson(QJsonObject &jsonObject) {
  jsonObject["accept"] = QString(acceptInputs()[0]);
  jsonObject["from_state"] = fromState()->label();
  jsonObject["to_state"] = toState()->label();
}

void Transition::readJson(QJsonObject &jsonObject) {
  setAcceptInput(jsonObject["accept"].toString()[0]);
  // Unfortunately states cannot be read from json at here
}

std::vector<QChar> Transition::acceptInputs() { return _acceptedInputs; }
