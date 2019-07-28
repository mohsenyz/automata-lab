#include "turingmachine_test.h"
#include "turingmachine.h"

using namespace AutomataLab;

void TuringMachineTest::test_run1() {
  Machine *machine = new TuringMachine();

  State *state1 = new State("A");
  state1->setInitial(true);
  state1->setFinal(true);

  Transition *transition1 = new TuringTransition(
      state1, state1, '0', '1', TuringTransition::Direction::RIGHT);
  Transition *transition2 = new TuringTransition(
      state1, state1, '1', '0', TuringTransition::Direction::RIGHT);

  machine->addState(state1);
  machine->addTransition(transition1);
  machine->addTransition(transition2);

  machine->prepareRun();
  Tape tape("110011100");
  machine->setTape(&tape);
  QCOMPARE(machine->run(), true);
  QCOMPARE(tape.toString(), "001100011#");
}

void TuringMachineTest::test_run2() {
  Machine *machine = new TuringMachine();
  State *state1 = new State("A");
  state1->setInitial(true);
  State *state2 = new State("B");
  state2->setFinal(true);
  Transition *transition1 = new TuringTransition(
      state1, state1, '1', '1', TuringTransition::Direction::RIGHT);
  Transition *transition2 = new TuringTransition(
      state1, state2, '0', 'F', TuringTransition::Direction::RIGHT);

  machine->addState(state1);
  machine->addState(state2);
  machine->addTransition(transition1);
  machine->addTransition(transition2);

  machine->prepareRun();
  Tape tape("1111110");
  machine->setTape(&tape);
  QCOMPARE(machine->run(), true);
  QCOMPARE(tape.toString(), "111111F#");

  machine->prepareRun();
  Tape tape1("111111");
  machine->setTape(&tape1);
  QCOMPARE(machine->run(), false);
}

void TuringMachineTest::test_stepByStepRun1() {}

void TuringMachineTest::test_stepByStepRun2() {}

void TuringMachineTest::initTestCase() {}

void TuringMachineTest::cleanupTestCase() {}

static TuringMachineTest test;
