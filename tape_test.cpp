#include "tape_test.h"
#include "tape.h"
#include <QtTest>

using namespace AutomataLab;

void TapeTest::initTestCase() {}

void TapeTest::cleanupTestCase() {}

void TapeTest::test_moveRight() {
  Tape tape("abc");
  QCOMPARE(tape.read(), "a");
  tape.moveRight();
  QCOMPARE(tape.read(), "b");
  tape.moveRight();
  QCOMPARE(tape.read(), "c");
  for (int i = 0; i < 10; i++) {
    tape.moveRight();
    QCOMPARE(tape.read(), BLANK_CHARACTER);
  }
}

void TapeTest::test_showAll() {
  Tape tape("abcdefg");
  QString result = "";
  while (tape.read() != BLANK_CHARACTER) {
    result += tape.read();
    tape.moveRight();
  }
  QCOMPARE(result, "abcdefg");
}
static TapeTest test;
