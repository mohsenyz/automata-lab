#include "turingmachine.h"
using namespace AutomataLab;

TuringMachine::~TuringMachine() {}

MachineType TuringMachine::type() { return TURING; }

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
