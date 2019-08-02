#include "automatascene.h"
#include "ui_utils.h"
#include <QDateTime>
#include <QGraphicsSceneMouseEvent>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

using namespace AutomataLab;

AutomataScene::AutomataScene(QObject *parent, MachineType machineType)
    : QGraphicsScene(parent) {
  setMachineType(machineType);
  setBackgroundBrush(Qt::white);
}

MachineType AutomataScene::machineType() const { return _machineType; }

void AutomataScene::setMachineType(MachineType type) { _machineType = type; }

AutomataScene::Mode AutomataScene::currentMode() const { return _currentMode; }

void AutomataScene::setCurrentMode(Mode mode) { _currentMode = mode; }

unsigned int AutomataScene::stateIndex() { return _stateIndex++; }

void AutomataScene::mouseDoubleClickEvent(
    QGraphicsSceneMouseEvent *mouseEvent) {
  if (mouseEvent->button() == Qt::LeftButton && !selectedItems().isEmpty()) {
    if (selectedItems().first()->type() == ItemType::StateItem) {
      emit stateEditLabel(dynamic_cast<State *>(selectedItems().first()));
    } else if (selectedItems().first()->type() == ItemType::TransitionItem) {
      emit transitionEditRule(
          dynamic_cast<Transition *>(selectedItems().first()));
    }
    selectedItems().first()->update();
  }
}

void AutomataScene::saveTo(QString fileName) {
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly)) {
    QMessageBox::critical(
        0, "Can't open file",
        "Can't open file to save. Please check directory permissions");
    return;
  }

  QJsonObject machineJson;

  Machine *machine = SCENE_MACHINE(this);
  machineJson["type"] = machine->type();
  std::vector<State *> allState = machine->allStates();
  QJsonArray statesJson;
  for (auto state : allState) {
    QJsonObject stateJson;
    stateJson["label"] = state->label();
    stateJson["is_initial"] = state->isInitial();
    stateJson["is_final"] = state->isFinal();
    QGraphicsItem *item = GRAPHICS_ITEM(state);
    stateJson["x"] = item->x();
    stateJson["y"] = item->y();
    statesJson.push_back(stateJson);
  }
  machineJson["states"] = statesJson;
  std::vector<Transition *> allTransitions = machine->allTransitions();
  QJsonArray transitionsJson;
  for (auto transition : allTransitions) {
    QJsonObject transitionJson;
    QChar accept = transition->acceptInputs()[0];
    transitionJson["accept"] = QString(accept);
    transitionJson["from_state"] = transition->fromState()->label();
    if (machine->type() == TURING) {
      TuringTransitionDrawable *ttd = DRAWABLE_TURING_TRANSITION(transition);
      transitionJson["write"] = QString(ttd->write());
      transitionJson["direction"] = ttd->direction();
      transitionJson["to_state"] = ttd->toState()->label();
    } else {
      DFATransitionDrawable *dtd = DRAWABLE_DFA_TRANSITION(transition);
      transitionJson["to_state"] = dtd->toState()->label();
    }
    transitionsJson.push_back(transitionJson);
  }

  machineJson["transitions"] = transitionsJson;
  machineJson["created_at"] = QDateTime::currentMSecsSinceEpoch();
  QJsonDocument document(machineJson);
  file.write(document.toJson());
  file.close();
}

void AutomataScene::loadFromJson(QJsonObject machineObject) {
  Machine *machine = SCENE_MACHINE(this);
  int type = machineObject["type"].toInt();
  QJsonArray statesArray = machineObject["states"].toArray();
  for (int i = 0; i < statesArray.size(); i++) {
    QJsonObject stateObject = statesArray[i].toObject();
    StateDrawable *sd = new StateDrawable(stateObject["label"].toString());
    sd->setInitial(stateObject["is_initial"].toBool());
    sd->setFinal(stateObject["is_final"].toBool());
    QPointF pos = QPointF(stateObject["x"].toInt(), stateObject["y"].toInt());
    if (type == TURING) {
      SCENE_TURING_MACHINE(this)->addState(sd, pos);
    } else {
      SCENE_DFA_MACHINE(this)->addState(
          sd, QPointF(stateObject["x"].toInt(), stateObject["y"].toInt()));
    }
    sd->setPos(pos);
    update();
  }

  QJsonArray transitionsArray = machineObject["transitions"].toArray();
  for (int i = 0; i < transitionsArray.size(); i++) {
    QJsonObject transitionObject = transitionsArray[i].toObject();
    StateDrawable *fromState = DRAWABLE_STATE(
        machine->stateByLabel(transitionObject["from_state"].toString()));
    StateDrawable *toState = DRAWABLE_STATE(
        machine->stateByLabel(transitionObject["to_state"].toString()));
    QChar accept = transitionObject["accept"].toString()[0];
    int x = transitionObject["x"].toInt(), y = transitionObject["y"].toInt();
    if (type == TURING) {
      int directionInt = transitionObject["direction"].toInt();
      TuringTransition::Direction direction = TuringTransition::LEFT;
      if (directionInt == 0) {
        direction = TuringTransition::RIGHT;
      }
      TuringTransitionDrawable *ttd = new TuringTransitionDrawable(
          fromState, toState, accept, transitionObject["write"].toString()[0],
          direction);
      SCENE_TURING_MACHINE(this)->addTransition(ttd);
    } else {
      DFATransitionDrawable *dtd =
          new DFATransitionDrawable(fromState, toState, accept);
      SCENE_DFA_MACHINE(this)->addTransition(dtd);
    }
    update();
  }
  update();
}
