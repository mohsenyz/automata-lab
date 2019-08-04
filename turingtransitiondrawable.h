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

/**
 * @brief The TuringTransitionDrawable class
 */
class TuringTransitionDrawable : public TuringTransition,
                                 public TransitionDrawable {
public:
  using TuringTransition::TuringTransition;

  /**
   * @brief TuringTransitionDrawable with multiple accepting input
   */
  TuringTransitionDrawable(StateDrawable *, StateDrawable *, std::vector<QChar>,
                           QChar, Direction);

  /**
   * @brief TuringTransitionDrawable with single accepting character
   */
  TuringTransitionDrawable(StateDrawable *, StateDrawable *, QChar, QChar,
                           Direction);

  /**
   * @brief Retuens box label, shown in transition black box
   * @return
   */
  QString getBoxLabel() override;
};

} // namespace AutomataLab

#endif // TURINGTRANSITIONDRAWABLE_H
