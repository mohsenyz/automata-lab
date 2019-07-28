#include "mainwindow.h"
#include "automatascene.h"
#include "tape.h"
#include "ui_mainwindow.h"
#include <QScrollBar>

using namespace AutomataLab;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->statusBar->showMessage("Welcome to auomata lab, You can read more about "
                             "automata lab in help tab");
  AutomataScene *scene = new AutomataScene(this);
  scene->setSceneRect(0, 0, 2000, 2000);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setRenderHints(QPainter::Antialiasing |
                                   QPainter::SmoothPixmapTransform);
  ui->graphicsView->centerOn(0, 0);
}

MainWindow::~MainWindow() { delete ui; }
