#include "turingtransition.h"

using namespace AutomataLab;

TuringTransition::TuringTransition(State *fromState, State *toState,
                                   std::vector<QChar> acceptedInputs,
                                   QChar write, Direction direction)
    : Transition(fromState, toState, acceptedInputs), _write(write),
      _direction(direction) {}

TuringTransition::TuringTransition(State *fromState, State *toState,
                                   QChar acceptedInput, QChar write,
                                   Direction direction)
    : Transition(fromState, toState, acceptedInput), _write(write),
      _direction(direction) {}

QChar TuringTransition::write() { return _write; }

TuringTransition::Direction TuringTransition::direction() { return _direction; }

void TuringTransition::setWrite(QChar write) { _write = write; }

void TuringTransition::setDirection(Direction direction) {
  _direction = direction;
}

TuringTransition::~TuringTransition() {}
