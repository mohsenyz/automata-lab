#include "dfamachine.h"

using namespace AutomataLab;

int DFAMachine::type() { return MachineType::DFA; }

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

std::vector<Transition *> DFAMachine::findAllTransitions(State *state) {
  std::vector<Transition *> result;
  for (auto transition : transitions) {
    DFATransition *dfaTransition = dynamic_cast<DFATransition *>(transition);
    if (*(dfaTransition->fromState()) == *state ||
        *(dfaTransition->toState()) == *state)
      result.push_back(transition);
  }
  return result;
}

bool DFAMachine::isHalted() {
  return (tape()->read() == BLANK_CHARACTER || halted ||
          currentState() == nullptr);
}

bool DFAMachine::isAccepted() {
  return (isHalted() && currentState()->isFinal());
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
