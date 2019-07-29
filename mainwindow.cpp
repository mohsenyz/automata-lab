#include "mainwindow.h"
#include "machine.h"
#include "turingmachinescene.h"
#include "ui_mainwindow.h"
#include <QScrollBar>

using namespace AutomataLab;
AutomataScene *scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->statusBar->showMessage("Welcome to auomata lab, You can read more about "
                             "automata lab in help tab");
  scene = new TuringMachineScene(this);
  scene->setSceneRect(0, 0, 2000, 2000);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setRenderHints(QPainter::Antialiasing |
                                   QPainter::SmoothPixmapTransform);
  ui->graphicsView->centerOn(0, 0);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_newStateBtn_clicked() {
  scene->setCurrentMode(AutomataScene::Mode::InsertState);
  ui->newStateBtn->setCheckable(true);
  ui->newStateBtn->setChecked(true);
}
