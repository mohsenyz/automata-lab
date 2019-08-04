#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QTest>
#include <vector>

/**
 * @brief The TestSuite class, Manage all test cases and test classes
 * All test classes must inherit this class to be recognized and runned
 */
class TestSuite : public QObject {
public:
  /**
   * @brief TestSuite
   * This constructer push constructed test case in a list
   */
  TestSuite();

  /**
   * @brief Runs test cases, with application arguments
   * @param int arguments count
   * @param char*[] list of arguments
   * @return
   */
  static int run(int, char *[]);

private:
  /**
   * @brief all test classes
   * @return
   */
  static std::vector<QObject *> &all();
};

#endif // TESTSUITE_H
