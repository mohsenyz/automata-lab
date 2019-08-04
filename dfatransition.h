#ifndef DFATRANSITION_H
#define DFATRANSITION_H
#include "transition.h"

namespace AutomataLab {

/**
 * @brief The DFATransition class, Holds automata dfa transition information
 */
class DFATransition : public Transition {
public:
  ~DFATransition();
  using Transition::Transition;
};

} // namespace AutomataLab

#endif // DFATRANSITION_H
