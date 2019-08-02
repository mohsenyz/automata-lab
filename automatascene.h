#ifndef AUTOMATASCENE_H
#define AUTOMATASCENE_H
#include "machine.h"
#include "statedrawable.h"
#include <QFile>
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
  void saveTo(QString);
  void loadFromJson(QJsonObject);

signals:
  void requestSelect();
  void transitionInserted(Transition *transition);
  void transitionEditRule(Transition *transition);
  void stateEditLabel(State *state);
  void stateSelected(State *);
  void stateUnselected();

protected:
  unsigned int stateIndex();
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
  Mode _currentMode;
  MachineType _machineType;
  unsigned int _stateIndex = 0;
};

} // namespace AutomataLab
#endif // AUTOMATASCENE_H
