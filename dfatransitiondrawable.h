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
/**
 * @brief The DFATransitionDrawable class
 */
class DFATransitionDrawable : public DFATransition, public TransitionDrawable {
public:
  using DFATransition::DFATransition;

  /**
   * @brief DFATransitionDrawable with multiple accepted characters
   */
  DFATransitionDrawable(StateDrawable *, StateDrawable *, std::vector<QChar>);

  /**
   * @brief DFATransitionDrawable with single accepted character
   */
  DFATransitionDrawable(StateDrawable *, StateDrawable *, QChar);

  /**
   * @brief getBoxLabel, returns label to be drawn in transition black box!
   * @return
   */
  QString getBoxLabel() override;
};

} // namespace AutomataLab

#endif // DFATRANSITIONDRAWABLE_H
