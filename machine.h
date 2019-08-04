#ifndef MACHINE_H
#define MACHINE_H

#include "state.h"
#include "tape.h"
#include "transition.h"
#include <QString>

namespace AutomataLab {

/**
 * @brief The MachineType enum
 */
enum MachineType { DFA = 0, TURING };

/**
 * @brief The Machine class, Base of dfa and turing
 */
class Machine {
public:
  /**
   * @brief Machine
   */
  Machine();
  virtual ~Machine();

  /**
   * @brief Adds state to automata
   */
  void addState(State *);

  /**
   * @brief Checks if state exists
   * @return
   */
  bool stateExists(State *);

  /**
   * @brief Returns automata initial state
   * @return
   */
  State *initialState();

  /**
   * @brief Checks if automata initial state exists
   * @return
   */
  bool initialStateExists();

  /**
   * @brief Adds a transition to automata
   */
  void addTransition(Transition *);

  /**
   * @brief Checks if transition exists
   * @return
   */
  bool transitionExists(Transition *);

  /**
   * @brief Find a transition by from state and accepted input
   * @return
   */
  Transition *findTransition(State *, QChar);

  /**
   * @brief Find state by label
   * @return
   */
  State *stateByLabel(QString);

  /**
   * @brief Clear all states
   */
  void clearStates();

  /**
   * @brief Clear all transitions
   */
  void clearTransitions();

  /**
   * @brief Clears tape
   */
  void clearTape();

  /**
   * @brief Removes a transition from automata
   */
  void removeTransition(Transition *);

  /**
   * @brief Removes state from automata
   */
  void removeState(State *);

  /**
   * @brief List all of states
   * @return
   */
  std::vector<State *> allStates();

  /**
   * @brief List of all transitions
   * @return
   */
  std::vector<Transition *> allTransitions();

  /**
   * @brief Prepares machine to be runned, setting current state to initial
   * state, clearing tape and etc
   */
  virtual void prepareRun();

  /**
   * @brief Sets machine input as tape
   */
  void setTape(Tape *);

  /**
   * @brief tape
   * @return
   */
  Tape *tape();
  void virtual nextStep() = 0;
  Transition *nextTransition();
  State *currentState();
  std::vector<Transition *> findAllTransitions(State *);
  std::vector<Transition *> findAllTransitionsBetween(State *, State *);
  virtual MachineType type() = 0;
  virtual bool isHalted() = 0;
  virtual bool isAccepted() = 0;
  virtual bool run() = 0;

private:
  Tape *_tape;
  State *_currentState;

protected:
  void setCurrentState(State *);
  std::vector<State *> states;
  std::vector<Transition *> transitions;
};

} // namespace AutomataLab

#endif // MACHINE_H
