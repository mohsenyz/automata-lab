#include "dfamachine_test.h"
#include "dfamachine.h"

using namespace AutomataLab;

void DFAMachineTest::test_run1() {
  Machine *machine = new DFAMachine();
  State *state1 = new State(tr("S"));
  state1->setInitial(true);

  State *state2 = new State(tr("F"));
  state2->setFinal(true);

  State *state3 = new State(tr("M0"));

  Transition *transition1 = new DFATransition(state1, state2, '1');
  Transition *transition2 = new DFATransition(state1, state1, '0');
  Transition *transition3 = new DFATransition(state2, state2, '0');
  Transition *transition4 = new DFATransition(state2, state3, '1');
  Transition *transition5 = new DFATransition(state3, state3, '0');
  Transition *transition6 = new DFATransition(state3, state1, '1');

  machine->addState(state1);
  machine->addState(state2);
  machine->addState(state3);
  machine->addTransition(transition1);
  machine->addTransition(transition2);
  machine->addTransition(transition3);
  machine->addTransition(transition4);
  machine->addTransition(transition5);
  machine->addTransition(transition6);

  machine->prepareRun();
  Tape tape("111");
  machine->setTape(&tape);
  QCOMPARE(machine->run(), false);

  machine->prepareRun();
  Tape tape1("11101");
  machine->setTape(&tape1);
  QCOMPARE(machine->run(), true);
}

void DFAMachineTest::test_run2() {
  Machine *machine = new DFAMachine();
  State *state1 = new State(tr("A"));
  state1->setInitial(true);

  State *state2 = new State(tr("B"));
  state2->setFinal(true);

  Transition *t1 = new DFATransition(state1, state1, '1');
  Transition *t2 = new DFATransition(state1, state2, '0');
  Transition *t3 = new DFATransition(state2, state2, '0');

  machine->addState(state1);
  machine->addState(state2);

  machine->addTransition(t1);
  machine->addTransition(t2);
  machine->addTransition(t3);

  machine->prepareRun();
  Tape tape("100");
  machine->setTape(&tape);
  QCOMPARE(machine->run(), true);

  machine->prepareRun();
  Tape tape1("11111111100");
  machine->setTape(&tape1);
  QCOMPARE(machine->run(), true);

  machine->prepareRun();
  Tape tape2("1111110");
  machine->setTape(&tape2);
  QCOMPARE(machine->run(), true);

  machine->prepareRun();
  Tape tape3("11111000000");
  machine->setTape(&tape3);
  QCOMPARE(machine->run(), true);

  machine->prepareRun();
  Tape tape4("1111100000011111");
  machine->setTape(&tape4);
  QCOMPARE(machine->run(), false);
}

void DFAMachineTest::test_stepByStepRun1() {}

void DFAMachineTest::test_stepByStepRun2() {}

void DFAMachineTest::initTestCase() {}

void DFAMachineTest::cleanupTestCase(){};

static DFAMachineTest test;
