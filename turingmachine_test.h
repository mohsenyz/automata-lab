#ifndef TURINGMACHINE_TEST_H
#define TURINGMACHINE_TEST_H

#include "testsuite.h"
#include <QTest>

class TuringMachineTest : public TestSuite {
  Q_OBJECT

public:
  using TestSuite::TestSuite;
private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_run1();
  void test_run2();
  void test_stepByStepRun1();
  void test_stepByStepRun2();
};

#endif // TURINGMACHINE_TEST_H
