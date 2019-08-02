#include "turingmachinescene.h"
#include "statedrawable.h"
#include "ui_utils.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <cmath>
using namespace AutomataLab;

TuringMachineScene::TuringMachineScene(QObject *parent)
    : AutomataScene(parent, MachineType::TURING) {}

void TuringMachineScene::addState(StateDrawable *state, QPointF position) {
  TuringMachine::addState(state);
  state->setPos(position - state->boundingRect().center());
  addItem(state);
}

void TuringMachineScene::addTransition(TuringTransitionDrawable *transition) {
  TuringMachine::addTransition(transition);
  addItem(transition);
  recurveTransitions(transition->fromState(), transition->toState());
  update();
}

void TuringMachineScene::recurveTransitions(State *fromState, State *toState) {
  std::vector<TuringTransition *> transitions =
      TuringMachine::findAllTransitionsBetween(fromState, toState);
  int curve = 0;
  for (auto tr : transitions) {
    TuringTransitionDrawable *transition =
        dynamic_cast<TuringTransitionDrawable *>(tr);
    if (transitions.size() > 1) {
      TuringTransition *prevTransition = transitions.at(transitions.size() - 2);
      if (transition->fromState() != prevTransition->fromState()) {
        curve *= -1;
      }
    }
    transition->setCurve(curve);
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

void TuringMachineScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (!selectedItems().isEmpty()) {
    update();
  }

  if (currentMode() == Mode::InsertTransition && tempLine != nullptr) {
    tempLine->setLine(QLineF(tempLine->line().p1(), mouseEvent->scenePos()));
  }

  AutomataScene::mouseMoveEvent(mouseEvent);
}

void TuringMachineScene::mouseReleaseEvent(
    QGraphicsSceneMouseEvent *mouseEvent) {
  QGraphicsScene::mouseReleaseEvent(mouseEvent);
  if (currentMode() == Mode::InsertTransition && tempLine != nullptr) {
    QList<QGraphicsItem *> list = items(mouseEvent->scenePos());
    TuringTransitionDrawable *ttd = nullptr;
    if (!list.empty() && list.first()->type() == ItemType::StateItem) {
      StateDrawable *fromState =
                        DRAWABLE_STATE(items(tempLine->line().p1()).first()),
                    *toState = DRAWABLE_STATE(list.first());
      ttd = new TuringTransitionDrawable(fromState, toState, ' ', ' ',
                                         TuringTransition::RIGHT);
      addTransition(ttd);
      update();
    }
    removeItem(tempLine);
    delete tempLine;
    tempLine = nullptr;
    if (ttd != nullptr)
      emit transitionInserted(ttd);
  }
}

void TuringMachineScene::keyPressEvent(QKeyEvent *keyEvent) {
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
        removeTransition(DRAWABLE_TURING_TRANSITION(selectedItem));
      }
    }
    break;
  }
}

void TuringMachineScene::removeTransition(
    TuringTransitionDrawable *transition) {
  State *fromState = transition->fromState(), *toState = transition->toState();
  removeItem(transition);
  TuringMachine::removeTransition(transition);
  delete transition;
  recurveTransitions(fromState, toState);
  update();
}

void TuringMachineScene::removeState(StateDrawable *state) {
  std::vector<TuringTransition *> list = findAllTransitions(state);
  for (auto transition : list) {
    removeTransition(DRAWABLE_TURING_TRANSITION(transition));
  }
  removeItem(state);
  TuringMachine::removeState(state);
  delete state;
  update();
}

void TuringMachineScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
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
    AutomataScene::mousePressEvent(mouseEvent);
  }
  if (currentMode() == Mode::InsertState && selectedItems().isEmpty()) {
    StateDrawable *state = new StateDrawable(getNewStateName(this));
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
