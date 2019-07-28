#include "dfatransition.h"

using namespace AutomataLab;

DFATransition::DFATransition(State *fromState, State *toState,
                             std::vector<QChar> acceptedInputs)
    : Transition(fromState, acceptedInputs), _toState(toState) {}

DFATransition::DFATransition(State *fromState, State *toState,
                             QChar acceptedInput)
    : Transition(fromState, acceptedInput), _toState(toState) {}

State *DFATransition::toState() { return _toState; }

bool DFATransition::operator==(DFATransition &transition) {
  return Transition::operator==(transition) &&
         *(transition.toState()) == *(this->toState());
}

DFATransition::~DFATransition() { delete _toState; }
