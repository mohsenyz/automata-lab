#include "automatascene.h"
#include "ui_utils.h"
#include <QGraphicsSceneMouseEvent>

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
