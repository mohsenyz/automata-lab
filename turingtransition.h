#ifndef TURINGTRANSITION_H
#define TURINGTRANSITION_H

#include "transition.h"

namespace AutomataLab {

/**
 * @brief The TuringTransition class, Holds a turing transition informations
 */
class TuringTransition : public Transition {
public:
  /**
   * @brief The Direction enum, Check if transition moves tape to right or left
   */
  enum Direction { RIGHT = 0, LEFT };

  using Transition::Transition;

  /**
   * @brief Constructs a turing transition from a state, to a state, with
   * accepted charactes, a write character and direction
   */
  TuringTransition(State *, State *, std::vector<QChar>, QChar, Direction);

  /**
   * @brief Constructs a turing transition from a state, to a state, with single
   * accepted charactr, a write character and direction
   */
  TuringTransition(State *, State *, QChar, QChar, Direction);
  ~TuringTransition();

  /**
   * @brief Returns write character
   * @return
   */
  QChar write();

  /**
   * @brief Returns transition direction
   * @return
   */
  Direction direction();

  /**
   * @brief Sets write character
   */
  void setWrite(QChar);

  /**
   * @brief Sets direction
   */
  void setDirection(Direction);

private:
  State *_toState;
  QChar _write = ' ';
  Direction _direction;
};

} // namespace AutomataLab

#endif // TURINGTRANSITION_H
