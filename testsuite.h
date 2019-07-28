#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QTest>
#include <vector>

class TestSuite : public QObject {
public:
  TestSuite();
  static int run(int, char *[]);

private:
  static std::vector<QObject *> &all();
};

#endif // TESTSUITE_H
