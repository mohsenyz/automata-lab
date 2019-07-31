#ifndef AUTOMATASCENE_H
#define AUTOMATASCENE_H
#include "machine.h"
#include "statedrawable.h"
#include <QGraphicsScene>

namespace AutomataLab {

class AutomataScene : public QGraphicsScene {
  Q_OBJECT
public:
  enum ItemType { StateItem, TransitionItem, TapeItem };
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
  void stateSelected(State *);
  void stateUnselected();

protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
  Mode _currentMode;
  MachineType _machineType;
};

} // namespace AutomataLab
#endif // AUTOMATASCENE_H
