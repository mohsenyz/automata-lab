#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"
#include <QChar>
#include <vector>

namespace AutomataLab {

class Transition {
public:
  Transition(State *, std::vector<QChar>);
  Transition(State *, QChar);
  virtual ~Transition();
  bool accepts(QChar);
  std::vector<QChar> acceptInputs();
  void setAcceptInputs(std::vector<QChar>);
  void setAcceptInput(QChar);
  State *fromState();
  virtual bool operator==(Transition &);

private:
  State *_fromState;
  std::vector<QChar> acceptedInputs;
};

} // namespace AutomataLab

#endif // TRANSITION_H
