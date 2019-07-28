#ifndef DFATRANSITION_H
#define DFATRANSITION_H
#include "transition.h"

namespace AutomataLab {

class DFATransition : public Transition {
public:
  ~DFATransition();
  DFATransition(State *, State *, std::vector<QChar>);
  DFATransition(State *, State *, QChar);
  State *toState();
  bool operator==(DFATransition &);

private:
  State *_toState;
};

} // namespace AutomataLab

#endif // DFATRANSITION_H
