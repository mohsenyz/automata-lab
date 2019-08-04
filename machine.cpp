#include "machine.h"
#include <algorithm>

using namespace AutomataLab;

Machine::Machine() {}

Machine::~Machine() {
  clearStates();
  clearTransitions();
}

void Machine::addState(State *state) {
  if (!stateExists(state))
    if (!(state->isInitial() && initialStateExists())) {
      states.push_back(state);
    }
}

void Machine::addTransition(Transition *transition) {
  if (!transitionExists(transition))
    transitions.push_back(transition);
}

void Machine::removeTransition(Transition *transition) {
  transitions.erase(
      std::remove(transitions.begin(), transitions.end(), transition),
      transitions.end());
}

void Machine::removeState(State *state) {
  states.erase(std::remove(states.begin(), states.end(), state), states.end());
}

bool Machine::transitionExists(Transition *transition) {
  for (auto _transition : transitions) {
    if (*_transition == *transition && _transition != transition)
      return true;
  }
  return false;
}

bool Machine::stateExists(State *state) {
  for (auto _state : states) {
    if (*_state == *state && _state != state)
      return true;
  }
  return false;
}

State *Machine::initialState() {
  for (auto state : states)
    if (state->isInitial())
      return state;
  return nullptr;
}

bool Machine::initialStateExists() { return initialState() != nullptr; }

Transition *Machine::findTransition(State *fromState, QChar input) {
  for (auto transition : transitions) {
    if (*(transition->fromState()) == *fromState && transition->accepts(input))
      return transition;
  }
  return nullptr;
}

State *Machine::stateByLabel(QString label) {
  for (auto state : states) {
    if (state->label() == label)
      return state;
  }
  return nullptr;
}

void Machine::clearStates() {
  for (auto state : states)
    delete state;
  states.clear();
}

void Machine::clearTransitions() {
  for (auto transition : transitions)
    delete transition;
  transitions.clear();
}

void Machine::prepareRun() {
  _tape = nullptr;
  _currentState = initialState();
  if (_currentState == nullptr) {
    throw std::runtime_error("No start state found");
  }
}

void Machine::clearTape() { delete _tape; }

Tape *Machine::tape() { return _tape; }

Transition *Machine::nextTransition() {
  return findTransition(currentState(), tape()->read());
}

void Machine::setCurrentState(State *state) { _currentState = state; }

State *Machine::currentState() { return _currentState; }

void Machine::setTape(Tape *input) { _tape = input; }

std::vector<State *> Machine::allStates() { return states; }

std::vector<Transition *> Machine::allTransitions() { return transitions; }

std::vector<Transition *> Machine::findAllTransitionsBetween(State *fState,
                                                             State *sState) {
  std::vector<Transition *> result;
  for (auto transition : transitions) {
    Transition *turingTransition = dynamic_cast<Transition *>(transition);
    bool fromFirstToSecond = *(turingTransition->fromState()) == *fState &&
                             *(turingTransition->toState()) == *sState;
    bool fromSecondToFirst = *(turingTransition->fromState()) == *sState &&
                             *(turingTransition->toState()) == *fState;
    if (fromFirstToSecond || fromSecondToFirst)
      result.push_back(turingTransition);
  }
  return result;
}

std::vector<Transition *> Machine::findAllTransitions(State *state) {
  std::vector<Transition *> result;
  for (auto transition : transitions) {
    Transition *turingTransition = dynamic_cast<Transition *>(transition);
    if (*(turingTransition->fromState()) == *state ||
        *(turingTransition->toState()) == *state)
      result.push_back(turingTransition);
  }
  return result;
}
