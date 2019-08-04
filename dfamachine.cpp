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
