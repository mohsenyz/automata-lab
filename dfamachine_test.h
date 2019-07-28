#ifndef DFAMACHINE_TEST_H
#define DFAMACHINE_TEST_H

#include "testsuite.h"
#include <QTest>

class DFAMachineTest : public TestSuite {
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

#endif // DFAMACHINE_TEST_H
