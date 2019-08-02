#include "mainwindow.h"
#include "dfamachinescene.h"
#include "ui_utils.h"
#include <QCheckBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMessageBox>
#include <QPalette>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <QSpacerItem>
#include <QTimer>
#include <QWidget>
#include <tapedrawable.h>

using namespace AutomataLab;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  QMessageBox msgBox;
  msgBox.setText("Select an automata to draw:");
  QPushButton *dfaButton = msgBox.addButton(tr("DFA"), QMessageBox::ActionRole);
  QPushButton *turingButton =
      msgBox.addButton(tr("Turing"), QMessageBox::ActionRole);
  msgBox.setStandardButtons(QMessageBox::Cancel);

  int ret = msgBox.exec();

  if (msgBox.clickedButton() == dfaButton) {
    automataScene = new DFAMachineScene(this);
    setWindowTitle(tr("AutomataLab - DFA"));
  } else if (msgBox.clickedButton() == turingButton) {
    automataScene = new TuringMachineScene(this);
    setWindowTitle(tr("AutomataLab - Turing"));
  }

  if (ret == QMessageBox::Cancel) {
    QTimer::singleShot(0, this, SLOT(close()));
    return;
  }
  init();
}

void MainWindow::init() {
  ui->setupUi(this);
  if (SCENE_MACHINE(automataScene)->type() == DFA) {
    setWindowTitle(tr("AutomataLab - DFA"));
  } else {
    setWindowTitle(tr("AutomataLab - Turing"));
  }

  ui->statusBar->showMessage("Welcome to auomata lab, You can read more about "
                             "automata lab in help tab");
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

  tapeScene = new QGraphicsScene(this);
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

  multipleRunLayout = new MultipleRunLayout(this, SCENE_MACHINE(automataScene));
  ui->toolBox->removeItem(1);
  multipleRunLayout->attach(ui->toolBox);
  multipleRunLayout->focus();
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
  } else if (automataScene->machineType() == DFA) {
    DFAMachineScene *tms = dynamic_cast<DFAMachineScene *>(automataScene);
    DFATransition *tt = dynamic_cast<DFATransition *>(transition);
    bool ok;
    QString labelText = QString(tt->acceptInputs()[0]);
    QString text = QInputDialog::getText(this, tr("Transition rule"),
                                         tr("Transition rule (Accept):"),
                                         QLineEdit::Normal, labelText, &ok);
    if (!text.trimmed().isEmpty() && ok) {
      tt->setAcceptInput(text.trimmed()[0]);
      if (tms->transitionExists(tt)) {
        QMessageBox::critical(0, "Error !",
                              "A transition from state : \"" +
                                  tt->fromState()->label() +
                                  "\" with accept character : \"" +
                                  tt->acceptInputs()[0] + "\" already exists!");
        transitionInserted(transition);
      }
      automataScene->update();
    } else if (!ok) {
      SCENE_DFA_MACHINE(automataScene)
          ->removeTransition(DRAWABLE_DFA_TRANSITION(transition));
    } else if (ok) {
      QMessageBox::critical(0, "Invalid rule",
                            "Rules must be in this format : "
                            "accpetCharacter . ex : 1");
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

void MainWindow::on_moveBtn_clicked() { requestSelect(); }

void MainWindow::on_newTransitionBtn_clicked() {
  uncheckToolBtns();
  automataScene->setCurrentMode(AutomataScene::Mode::InsertTransition);
  QApplication::setOverrideCursor(Qt::CrossCursor);
  ui->newTransitionBtn->setChecked(true);
}

void MainWindow::on_setInputBtn_clicked() {
  QString input = ui->lineEdit->text().trimmed();
  if (tapeDrawable != nullptr) {

    ui->tapeView->setBackgroundBrush(Qt::white);
    tapeScene->removeItem(tapeDrawable);
    delete tapeDrawable;
    tapeDrawable = nullptr;
  }
  if (input.contains(BLANK_CHARACTER)) {
    QMessageBox::critical(0, "Error!", "Input cannot contain blank character");
    return;
  }
  tapeDrawable = new TapeDrawable(input, SCENE_MACHINE(automataScene)->type());
  connect(tapeDrawable, SIGNAL(headMoved(QPointF)), this,
          SLOT(headMoved(QPointF)));
  tapeScene->addItem(tapeDrawable);
  ui->fastRunBtn->setEnabled(true);
  ui->nextStepBtn->setEnabled(true);
  ui->tapeView->setSceneRect(tapeScene->itemsBoundingRect());
}

void AutomataLab::MainWindow::on_fastRunBtn_clicked() {
  Machine *machine = SCENE_MACHINE(automataScene);
  if (!machine->initialStateExists()) {
    QMessageBox::critical(0, "Error!", "No initial state found!");
    return;
  }
  isRunning = true;
  tapeDrawable->setLocked(true);
  machine->prepareRun();
  machine->setTape(tapeDrawable);
  if (machine->run()) {
    QMessageBox::information(this, "Machine", "Input accepted!");
    ui->tapeView->setBackgroundBrush(QColor(129, 199, 132));
  } else {
    QMessageBox::critical(this, "Machine", "Input rejected!");
    ui->tapeView->setBackgroundBrush(QColor(229, 115, 115));
  }
  tapeDrawable->update();
  tapeScene->update();
  ui->tapeView->setSceneRect(tapeScene->itemsBoundingRect());
  clearRuntimeEnvironment();
}

void MainWindow::on_nextStepBtn_clicked() {
  Machine *machine = SCENE_MACHINE(automataScene);
  if (!machine->initialStateExists()) {
    QMessageBox::critical(0, "Error!", "No initial state found!");
    return;
  }
  if (!isRunning) {
    machine->prepareRun();

    isRunning = true;
    tapeDrawable->setLocked(true);
    ui->stopBtn->setEnabled(true);
    ui->setInputBtn->setEnabled(false);

    machine->setTape(tapeDrawable);
    DRAWABLE_STATE(machine->currentState())
        ->setBackgroundColor(QColor(255, 193, 7));
  } else {
    DRAWABLE_STATE(machine->currentState())
        ->setBackgroundColor(QColor(0, 188, 212));
    machine->nextStep();
    DRAWABLE_STATE(machine->currentState())
        ->setBackgroundColor(QColor(255, 193, 7));
    if (machine->isHalted()) {
      if (machine->isAccepted()) {
        QMessageBox::information(this, "Machine", "Input accepted!");
        ui->tapeView->setBackgroundBrush(QColor(129, 199, 132));
      } else {
        QMessageBox::critical(this, "Machine", "Input rejected!");
        ui->tapeView->setBackgroundBrush(QColor(229, 115, 115));
      }
      DRAWABLE_STATE(machine->currentState())
          ->setBackgroundColor(QColor(0, 188, 212));
      clearRuntimeEnvironment();
    }
  }
  ui->tapeView->setSceneRect(tapeScene->itemsBoundingRect());
  tapeDrawable->update();
  automataScene->update();
}

void MainWindow::on_file_newAction() {
  MainWindow *newMainWindow = new MainWindow();
  newMainWindow->setAttribute(Qt::WA_DeleteOnClose);
  newMainWindow->show();
}

void MainWindow::on_file_saveAction() {
  if (saveFileName.isEmpty()) {
    saveFileName = QFileDialog::getSaveFileName(
        this, tr("Save machine"), "/home/ubuntu/automata.aml",
        tr("AutomataLab file (*.aml))"));
    if (saveFileName.isEmpty()) {
      return;
    }
  }
  QFile file(saveFileName);
  automataScene->saveTo(saveFileName);
}

void MainWindow::on_file_saveAsAction() {}

void MainWindow::on_file_openAction() {
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Open machine"), "/home/ubuntu",
                                   tr("AutomataLab file (*.aml) "));
  if (fileName.isEmpty()) {
    QMessageBox::critical(0, "Error!", "File doesn't exist!");
    return;
  }
  MainWindow *newMainWindow = new MainWindow(fileName, nullptr);
  newMainWindow->setAttribute(Qt::WA_DeleteOnClose);
  newMainWindow->show();
}

MainWindow::MainWindow(QString fileName, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(0, "Can't open file",
                          "Can't open file to load machine!");
    QTimer::singleShot(0, this, SLOT(close()));
    return;
  }
  QByteArray saveData = file.readAll();
  QJsonObject machineObject = QJsonDocument::fromJson(saveData).object();
  if (machineObject["type"] == MachineType::TURING) {
    automataScene = new TuringMachineScene(this);
  } else {
    automataScene = new DFAMachineScene(this);
  }
  automataScene->loadFromJson(machineObject);
  init();
}

void MainWindow::on_file_saveAsImageAction() {}
void MainWindow::clearRuntimeEnvironment() {

  isRunning = false;
  ui->stopBtn->setEnabled(false);
  ui->fastRunBtn->setEnabled(false);
  ui->nextStepBtn->setEnabled(false);
  ui->setInputBtn->setEnabled(true);
}
