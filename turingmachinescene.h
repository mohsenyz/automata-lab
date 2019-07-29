#ifndef TURINGMACHINESCENE_H
#define TURINGMACHINESCENE_H

#include "automatascene.h"
#include "statedrawable.h"
#include "turingmachine.h"
#include "turingtransitiondrawable.h"

namespace AutomataLab {

class TuringMachineScene : public AutomataScene, public TuringMachine {
  Q_OBJECT
public:
  TuringMachineScene(QObject *parent);
  void addState(StateDrawable *, QPointF);
  void addTransition(TuringTransitionDrawable *transition);
signals:
  void stateInserted(StateDrawable *state);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
  QGraphicsLineItem *tempLine = nullptr;
};

} // namespace AutomataLab

#endif // TURINGMACHINESCENE_H
