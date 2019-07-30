#ifndef AUTOMATASCENE_H
#define AUTOMATASCENE_H
#include "machine.h"
#include "statedrawable.h"
#include <QGraphicsScene>

namespace AutomataLab {

class AutomataScene : public QGraphicsScene {
  Q_OBJECT
public:
  enum ItemType { StateItem, TransitionItem };
  enum Mode { InsertTransition, InsertState, Select };
  AutomataScene(QObject *parent, MachineType);
  MachineType machineType() const;
  void setMachineType(MachineType);
  Mode currentMode() const;
  void setCurrentMode(Mode);

signals:
  void requestSelect();
  void transitionInserted(Transition *transition);
  void transitionEditRule(Transition *transition);
  void stateEditLabel(State *state);

protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
  Mode _currentMode;
  MachineType _machineType;
};

} // namespace AutomataLab
#endif // AUTOMATASCENE_H
