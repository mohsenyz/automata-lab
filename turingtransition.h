#ifndef TURINGTRANSITION_H
#define TURINGTRANSITION_H

#include "transition.h"

namespace AutomataLab {

class TuringTransition : public Transition {
public:
  enum Direction { RIGHT = 0, LEFT };
  TuringTransition(State *, State *, std::vector<QChar>, QChar, Direction);
  TuringTransition(State *, State *, QChar, QChar, Direction);
  ~TuringTransition();
  State *toState();
  QChar write();
  Direction direction();
  void setWrite(QChar);
  void setDirection(Direction);

private:
  State *_toState;
  QChar _write = ' ';
  Direction _direction;
};

} // namespace AutomataLab

#endif // TURINGTRANSITION_H
