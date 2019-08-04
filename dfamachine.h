#ifndef DFAMACHINE_H
#define DFAMACHINE_H
#include "dfatransition.h"
#include "machine.h"

namespace AutomataLab {

/**
 * @brief The DFAMachine class
 */
class DFAMachine : public Machine {
public:
  using Machine::Machine;
  ~DFAMachine();

  /**
   * @brief Returns machine type, It's dfa now
   * @return
   */
  MachineType type();

  /**
   * @brief Leads machine to next steap
   */
  void nextStep();

  /**
   * @brief Returns true when dfa halted
   * @return
   */
  bool isHalted();

  /**
   * @brief Check if input is accepted by dfa
   * @return
   */
  bool isAccepted();

  /**
   * @brief Fast runs dfa and returns reject/accept status immediatly
   * @return
   */
  bool run();

  /**
   * @brief Prepares machine to run, clearing tapes and everything needed to run
   * machine
   */
  void prepareRun();

private:
  bool halted;
};

} // namespace AutomataLab

#endif // DFAMACHINE_H
