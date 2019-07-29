#include "automatascene.h"
#include "ui_utils.h"

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
