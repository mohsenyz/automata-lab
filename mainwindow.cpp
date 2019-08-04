#include "mainwindow.h"
#include "dfamachinescene.h"
#include "turingmachinescene.h"
#include "ui_utils.h"
#include <QCheckBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMessageBox>
#include <QNetworkReply>
#include <QPalette>
#include <QPdfWriter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <QSettings>
#include <QSpacerItem>
#include <QTimer>
#include <QWidget>
#include <tapedrawable.h>

using namespace AutomataLab;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  manager = new QNetworkAccessManager();
  connect(manager, SIGNAL(finished(QNetworkReply *)), this,
          SLOT(onActivationResultReceived(QNetworkReply *)));
  askForMachineType();
  ui->setupUi(this);
  initWindowTitle();
  initViews();
  initObservers();
  createToolboxPanels();
}

void MainWindow::onActivationResultReceived(QNetworkReply *reply) {
  if (reply->error()) {
    QMessageBox::critical(0, "Error!", "Failed to connect to internet");
    return;
  }
  QString answer = reply->readAll();
  if (answer.trimmed() == "403") {
    QMessageBox::critical(0, "Error!", "Invalid serial number");
  } else if (answer.trimmed() == "OK") {
    QMessageBox::information(0, "Software activated!",
                             "Software activated successfully!");
    QSettings settings("Mohsenyz", "Machine lab");
    settings.setValue("purchased", true);
  }
}

void MainWindow::on_help_productActivationAction() {
  bool ok;
  QString text = QInputDialog::getText(
      this, tr("Product activation"), tr("Enter serial to activate product"),
      QLineEdit::Normal, "Ex : 0021502350236", &ok);
  if (ok) {
    manager->get(QNetworkRequest(
        "http://git.playoffapp.ir:8898/apps/mohsenyz/validate?serial=" + text));
  }
}

void MainWindow::askForMachineType() {
  QMessageBox msgBox;
  msgBox.setText("Select an automata to draw:");
  QPushButton *dfaButton = msgBox.addButton(tr("DFA"), QMessageBox::ActionRole);
  QPushButton *turingButton =
      msgBox.addButton(tr("Turing"), QMessageBox::ActionRole);
  msgBox.setStandardButtons(QMessageBox::Cancel);

  int ret = msgBox.exec();

  if (msgBox.clickedButton() == dfaButton) {
    automataScene = new DFAMachineScene(this);
  } else if (msgBox.clickedButton() == turingButton) {
    QSettings settings("Mohsenyz", "Machine lab");
    if (!settings.value("purchased").toBool()) {
      QMessageBox::critical(
          0, "App is not activated",
          "Please activate the product from help menu, and try again");
      askForMachineType();
      return;
    }
    automataScene = new TuringMachineScene(this);
  }

  // User canceled the operation, close the window
  if (ret == QMessageBox::Cancel) {
    QTimer::singleShot(0, this, SLOT(close()));
    return;
  }
}

void MainWindow::initWindowTitle() {
  if (automataScene->machineType() == DFA) {
    setWindowTitle(tr("AutomataLab - DFA"));
  } else {
    setWindowTitle("AutomataLab - Turing");
  }
}

void MainWindow::initViews() {
  ui->statusBar->showMessage("Welcome to auomata lab, You can read more about "
                             "automata lab in help tab");
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
  ui->graphicsView->updateScene({automataScene->sceneRect()});
}

void MainWindow::initObservers() {
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
}

void MainWindow::headMoved(QPointF pos) {}

void MainWindow::stateSetInitial(StateDrawable *state) {
  if (MACHINE(automataScene)->initialStateExists() &&
      MACHINE(automataScene)->initialState() != state) {
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

  multipleRunLayout = new MultipleRunLayout(this, MACHINE(automataScene));
  ui->toolBox->removeItem(1);
  multipleRunLayout->attach(ui->toolBox);
  multipleRunLayout->focus();
}

void MainWindow::uncheckToolBtns() {
  ui->newStateBtn->setChecked(false);
  ui->newTransitionBtn->setChecked(false);
}

MainWindow::~MainWindow() {
  delete ui;
  delete inspectorLayout;
  delete multipleRunLayout;
  delete automataScene;
  delete tapeDrawable;
  delete tapeScene;
}

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
      automataScene->removeTransition(DRAWABLE_TURING_TRANSITION(transition));
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
    } else if (!ok && !labelText.trimmed().isEmpty()) {
      automataScene->removeTransition(DRAWABLE_DFA_TRANSITION(transition));
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
  tapeDrawable = new TapeDrawable(input, MACHINE(automataScene)->type());
  connect(tapeDrawable, SIGNAL(headMoved(QPointF)), this,
          SLOT(headMoved(QPointF)));
  tapeScene->addItem(tapeDrawable);
  ui->fastRunBtn->setEnabled(true);
  ui->nextStepBtn->setEnabled(true);
  tapeDrawable->setLocked(false);
  ui->tapeView->setSceneRect(tapeScene->itemsBoundingRect());
}

void AutomataLab::MainWindow::on_fastRunBtn_clicked() {
  Machine *machine = MACHINE(automataScene);
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
  Machine *machine = MACHINE(automataScene);
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

void MainWindow::on_file_saveAsAction() {
  saveFileName = QFileDialog::getSaveFileName(this, tr("Save machine"),
                                              "/home/ubuntu/automata.aml",
                                              tr("AutomataLab file (*.aml))"));
  if (saveFileName.isEmpty()) {
    return;
  }
  QFile file(saveFileName);
  automataScene->saveTo(saveFileName);
}

void MainWindow::loadSavedAutomata() {
  automataScene->loadFromJson(jsonObject);
  initWindowTitle();
}

void MainWindow::on_file_openAction() {
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Open machine"), "/home/ubuntu",
                                   tr("AutomataLab file (*.aml) "));
  if (fileName.isEmpty()) {
    QMessageBox::critical(0, "Error!", "File doesn't exist!");
    return;
  }
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(0, "Can't open file",
                          "Can't open file to load machine!");
    QTimer::singleShot(0, this, SLOT(close()));
    return;
  }
  QByteArray saveData = file.readAll();
  QJsonObject machineObject = QJsonDocument::fromJson(saveData).object();
  AutomataScene *oldScene = automataScene;
  if (machineObject["type"] == MachineType::TURING) {
    QSettings settings("Mohsenyz", "Machine lab");
    if (!settings.value("purchased").toBool()) {
      QMessageBox::critical(
          0, "App is not activated",
          "Please activate program from help menu to use Turing machine");
      return;
    }
    automataScene = new TuringMachineScene(this);
  } else {
    automataScene = new DFAMachineScene(this);
  }
  automataScene->setSceneRect(0, 0, 2000, 2000);
  jsonObject = machineObject;
  saveFileName = fileName;
  delete oldScene;
  multipleRunLayout->setMachine(MACHINE(automataScene));
  QTimer::singleShot(500, this, SLOT(loadSavedAutomata()));
  ui->graphicsView->setScene(automataScene);
  initObservers();
}

void MainWindow::on_file_saveAsImageAction() {
  saveFileName = QFileDialog::getSaveFileName(this, tr("Save machine as image"),
                                              "/home/ubuntu/automata.png",
                                              tr("Image file (*.png))"));
  if (saveFileName.isEmpty()) {
    return;
  }
  automataScene->clearSelection();
  QImage image(automataScene->sceneRect().size().toSize(),
               QImage::Format_ARGB32);
  image.fill(Qt::transparent);
  QPainter painter(&image);
  painter.setRenderHint(QPainter::Antialiasing);
  automataScene->render(&painter);
  image.save(saveFileName);
}

void MainWindow::clearRuntimeEnvironment() {
  isRunning = false;
  ui->stopBtn->setEnabled(false);
  ui->fastRunBtn->setEnabled(false);
  ui->nextStepBtn->setEnabled(false);
  ui->setInputBtn->setEnabled(true);
}

void MainWindow::on_file_saveAsPdf() {
  saveFileName = QFileDialog::getSaveFileName(this, tr("Save machine as pdf"),
                                              "/home/ubuntu/automata.pdf",
                                              tr("Pdf file (*.pdf))"));
  if (saveFileName.isEmpty()) {
    return;
  }
  automataScene->clearSelection();
  QImage image(automataScene->sceneRect().size().toSize(),
               QImage::Format_ARGB32);
  image.fill(Qt::transparent);
  QPainter painter(&image);
  painter.setRenderHint(QPainter::Antialiasing);
  automataScene->render(&painter);
  QPdfWriter pdfWriter(saveFileName);
  pdfWriter.setPageSize(QPagedPaintDevice::A4);
  pdfWriter.setResolution(1500);
  QPainter p(&pdfWriter);
  p.drawImage(QPoint(0, 0), image.scaled(pdfWriter.width(), pdfWriter.height(),
                                         Qt::AspectRatioMode::KeepAspectRatio));
  p.drawText(QPointF(0, pdfWriter.height() - 100), "Created by automata lab");
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  automataScene->update();
}

void MainWindow::on_newComponentBtn_clicked() {
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Open machine"), "/home/ubuntu",
                                   tr("AutomataLab file (*.aml) "));
  if (fileName.isEmpty()) {
    QMessageBox::critical(0, "Error!", "File doesn't exist!");
    return;
  }
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(0, "Can't open file",
                          "Can't open file to load machine!");
    QTimer::singleShot(0, this, SLOT(close()));
    return;
  }
  QByteArray saveData = file.readAll();
  QJsonObject machineObject = QJsonDocument::fromJson(saveData).object();
  automataScene->loadFromJson(machineObject, "A:");
}
