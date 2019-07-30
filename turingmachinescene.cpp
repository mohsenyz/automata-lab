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
  std::vector<TuringTransition *> transitions =
      TuringMachine::findAllTransitionsBetween(transition->fromState(),
                                               transition->toState());
  TuringMachine::addTransition(transition);
  int curve = transitions.size();
  int size = curve;
  if (abs(curve) > 0) {
    curve = ceil(curve / 2.0);
    if (size % 2 == 0)
      curve = curve * -1;
  }
  if (transition->fromState() == transition->toState()) {
    qDebug(std::to_string(size).c_str());
    transition->setCurve(size - 1);
  } else {
    transition->setCurve(curve);
  }
  addItem(transition);
}

void TuringMachineScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (!selectedItems().isEmpty()) {
    QGraphicsItem *item = selectedItems()[0];
    if (item->type() == ItemType::StateItem) {
      StateDrawable *drawable = DRAWABLE_STATE(item);
      std::vector<TuringTransition *> transitions =
          findAllTransitions(drawable);
      for (auto transition : transitions) {
        DRAWABLE_TURING_TRANSITION(transition)->updatePosition();
      }
    }
    update(sceneRect());
  }

  if (currentMode() == Mode::InsertTransition && tempLine != nullptr) {
    tempLine->setLine(QLineF(tempLine->line().p1(), mouseEvent->scenePos()));
  }

  AutomataScene::mouseMoveEvent(mouseEvent);
}

int stateIndex = 0;

void TuringMachineScene::mouseReleaseEvent(
    QGraphicsSceneMouseEvent *mouseEvent) {
  QGraphicsScene::mouseReleaseEvent(mouseEvent);
  if (currentMode() == Mode::InsertTransition && tempLine != nullptr) {
    QList<QGraphicsItem *> list = items(mouseEvent->scenePos());
    TuringTransitionDrawable *ttd = nullptr;
    if (!list.empty() && list.first()->type() == ItemType::StateItem) {
      StateDrawable *fromState =
          dynamic_cast<StateDrawable *>(items(tempLine->line().p1()).first());
      StateDrawable *toState = dynamic_cast<StateDrawable *>(list.first());
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
      if (selectedItems().first()->type() == ItemType::StateItem) {
        StateDrawable *sd =
            dynamic_cast<StateDrawable *>(selectedItems().first());
        std::vector<TuringTransition *> list = findAllTransitions(sd);
        for (auto transition : list) {
          removeItem(dynamic_cast<QGraphicsItem *>(transition));
          removeTransition(transition);
          delete transition;
        }
        removeItem(sd);
        removeState(sd);
        delete sd;
      } else if (selectedItems().first()->type() == ItemType::TransitionItem) {
        TuringTransitionDrawable *sd =
            dynamic_cast<TuringTransitionDrawable *>(selectedItems().first());
        removeItem(sd);
        removeTransition(sd);
        delete sd;
      }
    }
    break;
  }
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
    StateDrawable *state =
        new StateDrawable(tr("P") + QString::number(stateIndex));
    addState(state, mouseEvent->scenePos());
    stateIndex++;
  }
  if (!selectedItems().isEmpty() && currentMode() == Mode::InsertState) {
    emit requestSelect();
  }
}
