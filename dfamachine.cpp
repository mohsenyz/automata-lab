#include "dfamachine.h"

using namespace AutomataLab;

MachineType DFAMachine::type() { return MachineType::DFA; }

void DFAMachine::nextStep() {
  DFATransition *transition = dynamic_cast<DFATransition *>(
      findTransition(currentState(), tape()->read()));
  if (transition == nullptr) {
    halted = true;
    return;
  }
  setCurrentState(transition->toState());
  tape()->moveRight();
}

bool DFAMachine::isHalted() {
  return (tape()->read() == BLANK_CHARACTER || halted ||
          currentState() == nullptr || nextTransition() == nullptr ||
          tape()->currentIndex() == (tape()->inputSize()));
}

bool DFAMachine::isAccepted() {
  return (isHalted() && currentState()->isFinal() &&
          tape()->currentIndex() == (tape()->inputSize()));
}

bool DFAMachine::run() {
  do {
    nextStep();
  } while (!isHalted());
  return isAccepted();
}

void DFAMachine::prepareRun() {
  Machine::prepareRun();
  halted = false;
}

DFAMachine::~DFAMachine() {}

std::vector<DFATransition *>
DFAMachine::findAllTransitionsBetween(State *fState, State *sState) {
  std::vector<DFATransition *> result;
  for (auto transition : transitions) {
    DFATransition *turingTransition = dynamic_cast<DFATransition *>(transition);
    bool fromFirstToSecond = *(turingTransition->fromState()) == *fState &&
                             *(turingTransition->toState()) == *sState;
    bool fromSecondToFirst = *(turingTransition->fromState()) == *sState &&
                             *(turingTransition->toState()) == *fState;
    if (fromFirstToSecond || fromSecondToFirst)
      result.push_back(turingTransition);
  }
  return result;
}

std::vector<DFATransition *> DFAMachine::findAllTransitions(State *state) {
  std::vector<DFATransition *> result;
  for (auto transition : transitions) {
    DFATransition *turingTransition = dynamic_cast<DFATransition *>(transition);
    if (*(turingTransition->fromState()) == *state ||
        *(turingTransition->toState()) == *state)
      result.push_back(turingTransition);
  }
  return result;
}
