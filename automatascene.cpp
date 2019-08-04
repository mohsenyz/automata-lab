#include "automatascene.h"
#include "ui_utils.h"
#include <QApplication>
#include <QDateTime>
#include <QGraphicsSceneMouseEvent>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QMessageBox>
#include <cmath>

using namespace AutomataLab;

AutomataScene::AutomataScene(QObject *parent, MachineType machineType)
    : QGraphicsScene(parent), _machineType(machineType) {
  setBackgroundBrush(Qt::white);
}

MachineType AutomataScene::machineType() const { return _machineType; }

AutomataScene::Mode AutomataScene::currentMode() const { return _currentMode; }

void AutomataScene::setCurrentMode(Mode mode) { _currentMode = mode; }

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
  Machine *machine = MACHINE(this);
  machineJson["type"] = machine->type();

  // Serialize states
  std::vector<State *> allState = machine->allStates();
  QJsonArray statesJson;
  for (auto state : allState) {
    QJsonObject stateJson;
    SERIALIZABLE_ITEM(state)->writeJson(stateJson);
    statesJson.push_back(stateJson);
  }
  machineJson["states"] = statesJson;

  // Serialize transitions
  std::vector<Transition *> allTransitions = machine->allTransitions();
  QJsonArray transitionsJson;
  for (auto transition : allTransitions) {
    QJsonObject transitionJson;
    SERIALIZABLE_ITEM(DRAWABLE_TRANSITION(transition))
        ->writeJson(transitionJson);
    transitionsJson.push_back(transitionJson);
  }
  machineJson["transitions"] = transitionsJson;
  machineJson["created_at"] = QDateTime::currentMSecsSinceEpoch();
  QJsonDocument document(machineJson);
  file.write(document.toJson());
  file.close();
}

void AutomataScene::loadFromJson(QJsonObject machineObject,
                                 QString statePrefix) {
  Machine *machine = MACHINE(this);
  int type = machineObject["type"].toInt();
  QJsonArray statesArray = machineObject["states"].toArray();

  // Load states
  for (int i = 0; i < statesArray.size(); i++) {
    QJsonObject stateObject = statesArray[i].toObject();
    stateObject["label"] = statePrefix + stateObject["label"].toString();
    StateDrawable *sd = new StateDrawable();
    sd->readJson(stateObject);
    addState(sd, QPointF());
    update();
  }

  // Load transitions
  QJsonArray transitionsArray = machineObject["transitions"].toArray();
  for (int i = 0; i < transitionsArray.size(); i++) {
    QJsonObject transitionObject = transitionsArray[i].toObject();
    StateDrawable *fromState = DRAWABLE_STATE(machine->stateByLabel(
        statePrefix + transitionObject["from_state"].toString()));
    StateDrawable *toState = DRAWABLE_STATE(machine->stateByLabel(
        statePrefix + transitionObject["to_state"].toString()));
    TransitionDrawable *td;
    if (type == TURING) {
      td = new TuringTransitionDrawable(fromState, toState);
    } else {
      td = new DFATransitionDrawable(fromState, toState);
    }
    SERIALIZABLE_ITEM(TRANSITION(td))->readJson(transitionObject);
    addTransition(td);
    update();
  }
  update();
}

void AutomataScene::addState(StateDrawable *state, QPointF position) {
  MACHINE(this)->addState(state);
  if (!position.isNull())
    state->setPos(position - state->boundingRect().center());
  addItem(state);
}

void AutomataScene::addTransition(TransitionDrawable *transition) {
  MACHINE(this)->addTransition(TRANSITION(transition));
  addItem(transition);
  recurveTransitions(TRANSITION(transition)->fromState(),
                     TRANSITION(transition)->toState());
  update();
}

void AutomataScene::recurveTransitions(State *fromState, State *toState) {
  std::vector<Transition *> transitions =
      MACHINE(this)->findAllTransitionsBetween(fromState, toState);
  int curve = 0;
  for (auto tr : transitions) {
    if (transitions.size() > 1) {
      Transition *prevTransition = transitions.at(transitions.size() - 2);
      if (tr->fromState() != prevTransition->fromState()) {
        curve *= -1;
      }
    }
    DRAWABLE_TRANSITION(tr)->setCurve(curve);
    if (curve == 0) {
      curve++;
    } else {
      if (curve > 0) {
        curve = curve * -1;
      } else {
        curve = abs(curve) + 1;
      }
    }
  }
  if (transitions.size() > 0) {
    update();
  }
}

void AutomataScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (!selectedItems().isEmpty()) {
    update();
  }

  if (currentMode() == Mode::InsertTransition && tempLine != nullptr) {
    tempLine->setLine(QLineF(tempLine->line().p1(), mouseEvent->scenePos()));
  }

  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void AutomataScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  QGraphicsScene::mouseReleaseEvent(mouseEvent);
  if (currentMode() == Mode::InsertTransition && tempLine != nullptr) {
    QList<QGraphicsItem *> list = items(mouseEvent->scenePos());
    TransitionDrawable *td = nullptr;
    if (!list.empty() && list.first()->type() == ItemType::StateItem) {
      StateDrawable *fromState =
                        DRAWABLE_STATE(items(tempLine->line().p1()).first()),
                    *toState = DRAWABLE_STATE(list.first());
      if (machineType() == DFA) {
        td = new DFATransitionDrawable(fromState, toState, ' ');
      } else {
        td = new TuringTransitionDrawable(fromState, toState, ' ', ' ',
                                          TuringTransition::RIGHT);
      }
      addTransition(td);
      update();
    }
    removeItem(tempLine);
    delete tempLine;
    tempLine = nullptr;
    if (td != nullptr)
      emit transitionInserted(TRANSITION(td));
  }
}

void AutomataScene::keyPressEvent(QKeyEvent *keyEvent) {
  switch (keyEvent->key()) {
  case Qt::Key_Delete:
    if (!selectedItems().isEmpty()) {
      QGraphicsItem *selectedItem = selectedItems().first();

      // Delete state
      if (selectedItem->type() == ItemType::StateItem) {
        removeState(DRAWABLE_STATE(selectedItems().first()));
      }

      // Delete transition
      if (selectedItem->type() == ItemType::TransitionItem) {
        removeTransition(DRAWABLE_TRANSITION(selectedItem));
      }
    }
    break;
  }
}

void AutomataScene::removeTransition(TransitionDrawable *transition) {
  State *fromState = TRANSITION(transition)->fromState(),
        *toState = TRANSITION(transition)->toState();
  removeItem(transition);
  MACHINE(this)->removeTransition(TRANSITION(transition));
  delete transition;
  recurveTransitions(fromState, toState);
  update();
}

void AutomataScene::removeState(StateDrawable *state) {
  std::vector<Transition *> list = MACHINE(this)->findAllTransitions(state);
  for (auto transition : list) {
    removeTransition(DRAWABLE_TRANSITION(transition));
  }
  removeItem(state);
  MACHINE(this)->removeState(state);
  delete state;
  update();
}

void AutomataScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (currentMode() == Mode::InsertTransition) {
    QList<QGraphicsItem *> list = items(mouseEvent->scenePos());
    if (list.size() > 0) {
      if (list.first()->type() == ItemType::StateItem) {
        tempLine = new QGraphicsLineItem(
            QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        tempLine->setPen(QPen(QColor(60, 60, 60), 2));
        addItem(tempLine);
      }
    }
  } else {
    QGraphicsScene::mousePressEvent(mouseEvent);
  }
  if (currentMode() == Mode::InsertState && selectedItems().isEmpty()) {
    StateDrawable *state = new StateDrawable(getNewStateName(MACHINE(this)));
    addState(state, mouseEvent->scenePos());
  }
  if (!selectedItems().isEmpty() && currentMode() == Mode::InsertState) {
    emit requestSelect();
  }
  if (selectedItems().size() > 0) {
    if (selectedItems().first()->type() == ItemType::StateItem) {
      emit stateSelected(dynamic_cast<State *>(selectedItems().first()));
    }
  }
  if (selectedItems().size() == 0 ||
      (selectedItems().size() > 0 &&
       selectedItems().first()->type() == ItemType::TransitionItem)) {
    emit stateUnselected();
  }
}
