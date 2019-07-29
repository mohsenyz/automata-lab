#include "mainwindow.h"
#include <QScrollBar>

using namespace AutomataLab;
AutomataScene *scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->statusBar->showMessage("Welcome to auomata lab, You can read more about "
                             "automata lab in help tab");
  scene = new TuringMachineScene(this);
  connect(scene, SIGNAL(requestSelect()), this, SLOT(requestSelect()));
  scene->setSceneRect(0, 0, 2000, 2000);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setRenderHints(QPainter::Antialiasing |
                                   QPainter::SmoothPixmapTransform);
  ui->graphicsView->centerOn(0, 0);
}

void MainWindow::uncheckToolBtns() {
  ui->newStateBtn->setChecked(false);
  ui->newTransitionBtn->setChecked(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_newStateBtn_clicked() {
  uncheckToolBtns();
  scene->setCurrentMode(AutomataScene::Mode::InsertState);
  QApplication::setOverrideCursor(Qt::CrossCursor);
  ui->newStateBtn->setChecked(true);
}

void MainWindow::requestSelect() {
  uncheckToolBtns();
  scene->setCurrentMode(AutomataScene::Mode::Select);
  QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void AutomataLab::MainWindow::on_moveBtn_clicked() { requestSelect(); }

void AutomataLab::MainWindow::on_newTransitionBtn_clicked() {
  uncheckToolBtns();
  scene->setCurrentMode(AutomataScene::Mode::InsertTransition);
  QApplication::setOverrideCursor(Qt::CrossCursor);
  ui->newTransitionBtn->setChecked(true);
}
