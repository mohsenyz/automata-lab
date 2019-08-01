#include "turingmachine.h"
using namespace AutomataLab;

TuringMachine::~TuringMachine() {}

MachineType TuringMachine::type() { return TURING; }

std::vector<TuringTransition *>
TuringMachine::findAllTransitions(State *state) {
  std::vector<TuringTransition *> result;
  for (auto transition : transitions) {
    TuringTransition *turingTransition =
        dynamic_cast<TuringTransition *>(transition);
    if (*(turingTransition->fromState()) == *state ||
        *(turingTransition->toState()) == *state)
      result.push_back(turingTransition);
  }
  return result;
}

void TuringMachine::nextStep() {
  TuringTransition *transition = dynamic_cast<TuringTransition *>(
      findTransition(currentState(), tape()->read()));
  if (transition == nullptr) {
    halted = true;
    return;
  }
  tape()->write(transition->write());
  if (transition->direction() == TuringTransition::Direction::LEFT) {
    tape()->moveLeft();
  } else {
    tape()->moveRight();
  }
  setCurrentState(transition->toState());
}

bool TuringMachine::isHalted() {
  return halted || currentState() == nullptr || nextTransition() == nullptr;
}

bool TuringMachine::isAccepted() {
  return (isHalted() && currentState()->isFinal());
}

bool TuringMachine::run() {
  do {
    nextStep();
  } while (!isHalted());
  return isAccepted();
}

void TuringMachine::prepareRun() {
  Machine::prepareRun();
  halted = false;
}

std::vector<TuringTransition *>
TuringMachine::findAllTransitionsBetween(State *fState, State *sState) {
  std::vector<TuringTransition *> result;
  for (auto transition : transitions) {
    TuringTransition *turingTransition =
        dynamic_cast<TuringTransition *>(transition);
    bool fromFirstToSecond = *(turingTransition->fromState()) == *fState &&
                             *(turingTransition->toState()) == *sState;
    bool fromSecondToFirst = *(turingTransition->fromState()) == *sState &&
                             *(turingTransition->toState()) == *fState;
    if (fromFirstToSecond || fromSecondToFirst)
      result.push_back(turingTransition);
  }
  return result;
}
