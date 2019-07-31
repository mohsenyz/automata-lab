#include "mainwindow.h"
#include "ui_utils.h"
#include <QCheckBox>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QScrollBar>
#include <QSpacerItem>
#include <QWidget>
#include <tapedrawable.h>

using namespace AutomataLab;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->statusBar->showMessage("Welcome to auomata lab, You can read more about "
                             "automata lab in help tab");
  automataScene = new TuringMachineScene(this);
  connect(automataScene, SIGNAL(requestSelect()), this, SLOT(requestSelect()));
  connect(automataScene, SIGNAL(stateUnselected()), this,
          SLOT(stateUnselected()));
  connect(automataScene, SIGNAL(transitionInserted(Transition *)), this,
          SLOT(transitionInserted(Transition *)));
  connect(automataScene, SIGNAL(transitionEditRule(Transition *)), this,
          SLOT(transitionEditRule(Transition *)));
  connect(automataScene, SIGNAL(stateEditLabel(State *)), this,
          SLOT(stateEditLabel(State *)));
  connect(automataScene, SIGNAL(stateSelected(State *)), this,
          SLOT(stateSelected(State *)));
  automataScene->setSceneRect(0, 0, 2000, 2000);
  ui->graphicsView->setScene(automataScene);
  ui->graphicsView->setRenderHints(QPainter::Antialiasing |
                                   QPainter::SmoothPixmapTransform);
  ui->graphicsView->centerOn(0, 0);

  QGraphicsScene *tapeScene = new QGraphicsScene(this);
  //  TapeDrawable *tapeDrawable =
  //      new TapeDrawable("1110202020196785867545121176476034");
  //  connect(tapeDrawable, SIGNAL(headMoved(QPointF)), this,
  //          SLOT(headMoved(QPointF)));
  //  tapeScene->addItem(tapeDrawable);
  ui->tapeView->setScene(tapeScene);
  ui->tapeView->setRenderHints(QPainter::Antialiasing |
                               QPainter::SmoothPixmapTransform);
  ui->tapeView->centerOn(0, 0);
  createToolboxPanels();
}

void MainWindow::headMoved(QPointF pos) {}

void MainWindow::stateSetInitial(StateDrawable *state) {
  if (SCENE_MACHINE(automataScene)->initialStateExists() &&
      SCENE_MACHINE(automataScene)->initialState() != state) {
    QMessageBox::critical(0, tr("Error!"),
                          tr("An automata can't have multiple initial state"));
    return;
  }
  state->setInitial(true);
  state->update();
}

void MainWindow::createToolboxPanels() {
  inspectorLayout = new InspectorLayout(this);
  connect(inspectorLayout, SIGNAL(stateSetInitial(StateDrawable *)), this,
          SLOT(stateSetInitial(StateDrawable *)));
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
  if (automataScene->machineType() == TURING) {
    TuringMachineScene *tms = dynamic_cast<TuringMachineScene *>(automataScene);
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
        QMessageBox::critical(0, "Error !",
                              "A transition from state : \"" +
                                  tt->fromState()->label() +
                                  "\" with accept character : \"" +
                                  tt->acceptInputs()[0] + "\" already exists!");
        transitionInserted(transition);
      }
      automataScene->update();
    } else if (!ok && tt->write() == ' ') {
      SCENE_TURING_MACHINE(automataScene)
          ->removeTransition(DRAWABLE_TURING_TRANSITION(transition));
    } else if (ok) {
      QMessageBox::critical(0, "Invalid rule",
                            "Rules must be in this format : "
                            "accpetChar,writeChar,direction. ex : 1,0,R");
      transitionInserted(transition);
    }
  }
}

void MainWindow::stateEditLabel(State *state) {
  Machine *machine = dynamic_cast<Machine *>(automataScene);
  bool ok;
  QString text =
      QInputDialog::getText(this, tr("State label"), tr("State label :"),
                            QLineEdit::Normal, state->label(), &ok);
  if (ok) {
    QString prevLabel = state->label();
    state->setLabel(text);
    if (machine->stateExists(state)) {
      state->setLabel(prevLabel);
      QMessageBox::critical(0, "Invalid label",
                            "Label : \"" + text + "\" already exists!");
      stateEditLabel(state);
    }
  }
  update();
  inspectorLayout->invalidate();
}

void MainWindow::stateUnselected() { inspectorLayout->setState(nullptr); }

void MainWindow::transitionInserted(Transition *transition) {
  requestSelect();
  transitionEditRule(transition);
}
void MainWindow::on_newStateBtn_clicked() {
  uncheckToolBtns();
  automataScene->setCurrentMode(AutomataScene::Mode::InsertState);
  QApplication::setOverrideCursor(Qt::CrossCursor);
  ui->newStateBtn->setChecked(true);
}

void MainWindow::requestSelect() {
  uncheckToolBtns();
  automataScene->setCurrentMode(AutomataScene::Mode::Select);
  QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void AutomataLab::MainWindow::on_moveBtn_clicked() { requestSelect(); }

void AutomataLab::MainWindow::on_newTransitionBtn_clicked() {
  uncheckToolBtns();
  automataScene->setCurrentMode(AutomataScene::Mode::InsertTransition);
  QApplication::setOverrideCursor(Qt::CrossCursor);
  ui->newTransitionBtn->setChecked(true);
}
