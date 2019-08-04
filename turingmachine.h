#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H
#include "machine.h"
#include "turingtransition.h"

namespace AutomataLab {

/**
 * @brief The TuringMachine class
 */
class TuringMachine : public Machine {
public:
  using Machine::Machine;
  ~TuringMachine();

  /**
   * @brief Returns machine type, now Turing
   * @return
   */
  MachineType type();

  /**
   * @brief Leads machine to next step
   */
  void nextStep();

  /**
   * @brief Checks if machine halted
   * @return
   */
  bool isHalted();

  /**
   * @brief Checks if input is accepted
   * @return
   */
  bool isAccepted();

  /**
   * @brief Fast runs input and returns rejected/accepted state by false/true
   * @return
   */
  bool run();

  /**
   * @brief Prepares machine to run, means clearing tape, clearing current state
   * and etc
   */
  void prepareRun();

private:
  bool halted;
};

} // namespace AutomataLab

#endif // TURINGMACHINE_H
