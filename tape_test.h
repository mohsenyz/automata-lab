#ifndef TAPE_TEST_H
#define TAPE_TEST_H

#include "testsuite.h"
#include <QTest>

class TapeTest : public TestSuite {
  Q_OBJECT

public:
  using TestSuite::TestSuite;
private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_moveRight();
  void test_showAll();
};

#endif // TAPE_TEST_H
