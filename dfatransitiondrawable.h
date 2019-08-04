#ifndef DFATRANSITIONDRAWABLE_H
#define DFATRANSITIONDRAWABLE_H

#include "automatascene.h"
#include "dfatransition.h"
#include "statedrawable.h"
#include "transitiondrawable.h"
#include <QGraphicsLineItem>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>

namespace AutomataLab {

class DFATransitionDrawable : public DFATransition, public TransitionDrawable {
public:
  using DFATransition::DFATransition;
  DFATransitionDrawable(StateDrawable *, StateDrawable *, std::vector<QChar>);

  DFATransitionDrawable(StateDrawable *, StateDrawable *, QChar);
  QString getBoxLabel() override;
};

} // namespace AutomataLab

#endif // DFATRANSITIONDRAWABLE_H
