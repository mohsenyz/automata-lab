#include "turingtransitiondrawable.h"
#include "ui_utils.h"
using namespace AutomataLab;

#include <cmath>
#include <qmath.h>

TuringTransitionDrawable::TuringTransitionDrawable(
    StateDrawable *startState, StateDrawable *endState,
    std::vector<QChar> acceptedInputs, QChar write, Direction direction)
    : TuringTransition(startState, endState, acceptedInputs, write, direction),
      TransitionDrawable() {}

TuringTransitionDrawable::TuringTransitionDrawable(StateDrawable *startState,
                                                   StateDrawable *endState,
                                                   QChar acceptedInput,
                                                   QChar write,
                                                   Direction direction)
    : TuringTransition(startState, endState, acceptedInput, write, direction),
      TransitionDrawable() {}

QString TuringTransitionDrawable::getBoxLabel() {
  QString directionLabel = "L";
  if (direction() == Direction::RIGHT) {
    directionLabel = "R";
  }
  QString labelText = QString(acceptInputs()[0]) + "," + QString(write()) +
                      "," + directionLabel;
  return labelText;
}
