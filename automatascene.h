#ifndef AUTOMATASCENE_H
#define AUTOMATASCENE_H
#include "machine.h"
#include "statedrawable.h"
#include "transitiondrawable.h"
#include <QFile>
#include <QGraphicsScene>
namespace AutomataLab {

class AutomataScene : public QGraphicsScene {
  Q_OBJECT
public:
  enum ItemType { StateItem, TransitionItem, TapeItem };
  enum Mode { InsertTransition, InsertState, Select };
  AutomataScene(QObject *parent, MachineType);
  virtual MachineType machineType() const;
  Mode currentMode() const;
  void setCurrentMode(Mode);
  void saveTo(QString);
  void loadFromJson(QJsonObject, QString statePrefix = "");
  void addState(StateDrawable *, QPointF);
  void addTransition(TransitionDrawable *transition);
  void removeTransition(TransitionDrawable *transition);
  void removeState(StateDrawable *state);

signals:
  void requestSelect();
  void transitionInserted(Transition *transition);
  void transitionEditRule(Transition *transition);
  void stateEditLabel(State *state);
  void stateSelected(State *);
  void stateUnselected();

protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void keyPressEvent(QKeyEvent *keyEvent) override;

private:
  Mode _currentMode = Mode::Select;
  MachineType _machineType;
  void recurveTransitions(State *fromState, State *toState);
  QGraphicsLineItem *tempLine = nullptr;
};

} // namespace AutomataLab
#endif // AUTOMATASCENE_H
