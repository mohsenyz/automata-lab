#include "testsuite.h"

TestSuite::TestSuite() { all().push_back(this); }

std::vector<QObject *> &TestSuite::all() {
  static std::vector<QObject *> objects;
  return objects;
}

int TestSuite::run(int argc, char *argv[]) {
  int status = 0;
  auto runTest = [&status, argc, argv](QObject *obj) {
    status |= QTest::qExec(obj, argc, argv);
  };

  auto &suite = TestSuite::all();
  for (auto it = suite.begin(); it != suite.end(); ++it) {
    runTest(*it);
  }

  return status;
}
