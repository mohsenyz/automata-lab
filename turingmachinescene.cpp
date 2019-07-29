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
  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

int stateIndex = 0;

void TuringMachineScene::mouseReleaseEvent(
    QGraphicsSceneMouseEvent *mouseEvent) {
  if (currentMode() == Mode::InsertState) {
    setCurrentMode(Mode::Select);
    addState(new StateDrawable(tr("P") + QString::number(stateIndex)),
             mouseEvent->scenePos());
    stateIndex++;
  }
}

void TuringMachineScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

}
