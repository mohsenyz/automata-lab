#include "dfatransitiondrawable.h"
#include "ui_utils.h"
using namespace AutomataLab;

#include <cmath>
#include <qmath.h>

DFATransitionDrawable::DFATransitionDrawable(StateDrawable *startState,
                                             StateDrawable *endState,
                                             std::vector<QChar> acceptedInputs)
    : DFATransition(startState, endState, acceptedInputs),
      TransitionDrawable() {}

DFATransitionDrawable::DFATransitionDrawable(StateDrawable *startState,
                                             StateDrawable *endState,
                                             QChar acceptedInput)
    : DFATransition(startState, endState, acceptedInput), TransitionDrawable() {
}

QString DFATransitionDrawable::getBoxLabel() { return acceptInputs()[0]; }
