#include "mainwindow.h"
#include "tape_test.h"
#include "testsuite.h"
#include <QApplication>
using namespace AutomataLab;
int main(int argc, char *argv[]) {

  // Running tests before running app
  int status = TestSuite::run(argc, argv);
  if (status != 0) {
    qDebug("Unfortunately tests were not passed");
    exit(1);
  }

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
