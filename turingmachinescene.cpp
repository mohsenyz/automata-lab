#include "turingmachinescene.h"
#include "statedrawable.h"
#include "ui_utils.h"
#include <QGraphicsSceneMouseEvent>
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
}

void TuringMachineScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (!selectedItems().isEmpty()) {
    QGraphicsItem *item = selectedItems()[0];
    if (item->type() == ItemType::State) {
      StateDrawable *drawable = DRAWABLE_STATE(item);
      std::vector<AutomataLab::Transition *> transitions =
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
    if (!list.empty() && list.first()->type() == ItemType::State) {
      StateDrawable *fromState =
          dynamic_cast<StateDrawable *>(items(tempLine->line().p1()).first());
      StateDrawable *toState = dynamic_cast<StateDrawable *>(list.first());
      addTransition(new TuringTransitionDrawable(fromState, toState, ' ', ' ',
                                                 TuringTransition::RIGHT));
      emit requestSelect();
    }
    removeItem(tempLine);
    delete tempLine;
  }
}

void TuringMachineScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (currentMode() == Mode::InsertTransition) {
    QList<QGraphicsItem *> list = items(mouseEvent->scenePos());
    if (list.size() > 0) {
      if (list.first()->type() == ItemType::State) {
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
