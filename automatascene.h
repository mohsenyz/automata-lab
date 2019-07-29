#ifndef AUTOMATASCENE_H
#define AUTOMATASCENE_H
#include "turingmachine.h"
#include <QGraphicsScene>

namespace AutomataLab {

class AutomataScene : public QGraphicsScene {

public:
  enum ItemType { State, Transition };
  enum Mode { InsertTransition, InsertState, Select };
  AutomataScene(QObject *parent, MachineType);
  MachineType machineType() const;
  void setMachineType(MachineType);
  Mode currentMode() const;
  void setCurrentMode(Mode);

private:
  Mode _currentMode;
  MachineType _machineType;
};

} // namespace AutomataLab
#endif // AUTOMATASCENE_H
