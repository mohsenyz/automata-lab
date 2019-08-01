#ifndef DFAMACHINE_H
#define DFAMACHINE_H
#include "dfatransition.h"
#include "machine.h"

namespace AutomataLab {

class DFAMachine : public Machine {
public:
  using Machine::Machine;
  ~DFAMachine();
  MachineType type();
  std::vector<DFATransition *> findAllTransitions(State *);
  std::vector<DFATransition *> findAllTransitionsBetween(State *, State *);
  void nextStep();
  bool isHalted();
  bool isAccepted();
  bool run();
  void prepareRun();

private:
  bool halted;
};

} // namespace AutomataLab

#endif // DFAMACHINE_H
