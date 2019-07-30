#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H
#include "machine.h"
#include "turingtransition.h"

namespace AutomataLab {

class TuringMachine : public Machine {
public:
  using Machine::Machine;
  ~TuringMachine();
  int type();
  std::vector<TuringTransition *> findAllTransitions(State *);
  std::vector<TuringTransition *> findAllTransitionsBetween(State *, State *);
  void nextStep();
  bool isHalted();
  bool isAccepted();
  bool run();
  void prepareRun();

private:
  bool halted;
};

} // namespace AutomataLab

#endif // TURINGMACHINE_H
