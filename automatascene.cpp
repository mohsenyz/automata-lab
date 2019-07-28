#include "automatascene.h"
#include "statedrawable.h"

using namespace AutomataLab;

AutomataScene::AutomataScene(QObject *parent) : QGraphicsScene(parent) {
  setBackgroundBrush(Qt::white);

  StateDrawable *fPoint = new StateDrawable(tr("P1"));
  addItem(fPoint);

  StateDrawable *sPoint = new StateDrawable(tr("P2"));
  addItem(sPoint);
}
