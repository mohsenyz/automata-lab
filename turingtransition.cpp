#include "turingtransition.h"

using namespace AutomataLab;

TuringTransition::TuringTransition(State *fromState, State *toState,
                                   std::vector<QChar> acceptedInputs,
                                   QChar write, Direction direction)
    : Transition(fromState, acceptedInputs), _toState(toState), _write(write),
      _direction(direction) {}

TuringTransition::TuringTransition(State *fromState, State *toState,
                                   QChar acceptedInput, QChar write,
                                   Direction direction)
    : Transition(fromState, acceptedInput), _toState(toState), _write(write),
      _direction(direction) {}

State *TuringTransition::toState() { return _toState; }

QChar TuringTransition::write() { return _write; }

TuringTransition::Direction TuringTransition::direction() { return _direction; }

TuringTransition::~TuringTransition() {}
