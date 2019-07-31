#include "mainwindow.h"
#include "ui_utils.h"
#include <QCheckBox>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QScrollBar>
#include <QSpacerItem>
#include <QWidget>

using namespace AutomataLab;
AutomataScene *scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->statusBar->showMessage("Welcome to auomata lab, You can read more about "
                             "automata lab in help tab");
  scene = new TuringMachineScene(this);
  connect(scene, SIGNAL(requestSelect()), this, SLOT(requestSelect()));
  connect(scene, SIGNAL(transitionInserted(Transition *)), this,
          SLOT(transitionInserted(Transition *)));
  connect(scene, SIGNAL(transitionEditRule(Transition *)), this,
          SLOT(transitionEditRule(Transition *)));
  connect(scene, SIGNAL(stateEditLabel(State *)), this,
          SLOT(stateEditLabel(State *)));
  connect(scene, SIGNAL(stateSelected(State *)), this,
          SLOT(stateSelected(State *)));
  scene->setSceneRect(0, 0, 2000, 2000);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setRenderHints(QPainter::Antialiasing |
                                   QPainter::SmoothPixmapTransform);
  ui->graphicsView->centerOn(0, 0);

  createToolboxPanels();
}

void MainWindow::createToolboxPanels() {
  inspectorLayout = new InspectorLayout(this);
  ui->toolBox->removeItem(0);
  inspectorLayout->attach(ui->toolBox);
  ui->toolBox->insertItem(1, new QWidget(this), "Multiple run");
}

void MainWindow::uncheckToolBtns() {
  ui->newStateBtn->setChecked(false);
  ui->newTransitionBtn->setChecked(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::stateSelected(State *state) {
  inspectorLayout->focus();
  inspectorLayout->setState(DRAWABLE_STATE(state));
}

void MainWindow::transitionEditRule(Transition *transition) {
  if (scene->machineType() == TURING) {
    TuringMachineScene *tms = dynamic_cast<TuringMachineScene *>(scene);
    TuringTransition *tt = dynamic_cast<TuringTransition *>(transition);
    bool ok;
    QString direction = "L";
    if (tt->direction() == TuringTransition::Direction::RIGHT) {
      direction = "R";
    }
    QString labelText = QString(tt->acceptInputs()[0]) + "," +
                        QString(tt->write()) + "," + direction;
    QString text =
        QInputDialog::getText(this, tr("Transition rule"),
                              tr("Transition rule (Accept,Write,Direction):"),
                              QLineEdit::Normal, labelText, &ok);
    QStringList list = text.split(",");
    if (list.size() == 3 && text.size() == 5 &&
        (list.last() == "R" || list.last() == "L") && list[0][0] != ' ' &&
        list[1][0] != ' ' && ok) {
      tt->setAcceptInput(list[0][0]);
      tt->setWrite(list[1][0]);
      if (list.last() == "R") {
        tt->setDirection(TuringTransition::Direction::RIGHT);
      } else {
        tt->setDirection(TuringTransition::Direction::LEFT);
      }
      if (tms->transitionExists(tt)) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error !",
                            "A transition from state : \"" +
                                tt->fromState()->label() +
                                "\" with accept character : \"" +
                                tt->acceptInputs()[0] + "\" already exists!");
        messageBox.show();
        transitionInserted(transition);
      }
      scene->update();
    } else if (!ok && tt->write() == ' ') {
      SCENE_TURING_MACHINE(scene)->removeTransition(
          DRAWABLE_TURING_TRANSITION(transition));
    } else if (ok) {
      QMessageBox messageBox;
      messageBox.critical(0, "Invalid rule",
                          "Rules must be in this format : "
                          "accpetChar,writeChar,direction. ex : 1,0,R");
      messageBox.show();
      transitionInserted(transition);
    }
  }
}

void MainWindow::stateEditLabel(State *state) {
  Machine *machine = dynamic_cast<Machine *>(scene);
  bool ok;
  QString text =
      QInputDialog::getText(this, tr("State label"), tr("State label :"),
                            QLineEdit::Normal, state->label(), &ok);
  if (ok) {
    state->setLabel(text);
    if (machine->stateExists(state)) {
      QMessageBox messageBox;
      messageBox.critical(0, "Invalid label",
                          "Label : \"" + text + "\" already exists!");
      messageBox.show();
      stateEditLabel(state);
    }
  }
  update();
  inspectorLayout->invalidate();
}

void MainWindow::transitionInserted(Transition *transition) {
  requestSelect();
  transitionEditRule(transition);
}
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
