#ifndef DFAMACHINESCENE_H
#define DFAMACHINESCENE_H

#include "automatascene.h"
#include "dfamachine.h"
#include "dfatransitiondrawable.h"
#include "statedrawable.h"

namespace AutomataLab {

class DFAMachineScene : public AutomataScene, public DFAMachine {
  Q_OBJECT
public:
  DFAMachineScene(QObject *parent);
  void addState(StateDrawable *, QPointF);
  void addTransition(DFATransitionDrawable *transition);
  void removeTransition(DFATransitionDrawable *transition);
  void removeState(StateDrawable *state);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void keyPressEvent(QKeyEvent *keyEvent) override;

private:
  void recurveTransitions(State *fromState, State *toState);
  QGraphicsLineItem *tempLine = nullptr;
};

} // namespace AutomataLab

#endif // DFAMACHINESCENE_H
