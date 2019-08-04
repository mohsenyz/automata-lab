#ifndef TURINGTRANSITIONDRAWABLE_H
#define TURINGTRANSITIONDRAWABLE_H

#include "automatascene.h"
#include "statedrawable.h"
#include "transitiondrawable.h"
#include "turingtransition.h"
#include <QGraphicsLineItem>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>

namespace AutomataLab {

class TuringTransitionDrawable : public TuringTransition,
                                 public TransitionDrawable {
public:
  using TuringTransition::TuringTransition;
  TuringTransitionDrawable(StateDrawable *, StateDrawable *, std::vector<QChar>,
                           QChar, Direction);

  TuringTransitionDrawable(StateDrawable *, StateDrawable *, QChar, QChar,
                           Direction);

  QString getBoxLabel() override;
};

} // namespace AutomataLab

#endif // TURINGTRANSITIONDRAWABLE_H
