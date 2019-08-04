#ifndef MACHINE_H
#define MACHINE_H

#include "state.h"
#include "tape.h"
#include "transition.h"
#include <QString>

namespace AutomataLab {

enum MachineType { DFA = 0, TURING };

class Machine {
public:
  Machine();
  virtual ~Machine();
  void addState(State *);
  bool stateExists(State *);
  State *initialState();
  bool initialStateExists();
  void addTransition(Transition *);
  bool transitionExists(Transition *);
  Transition *findTransition(State *, QChar);
  State *stateByLabel(QString);
  void clearStates();
  void clearTransitions();
  void clearTape();
  void removeTransition(Transition *);
  void removeState(State *);
  std::vector<State *> allStates();
  std::vector<Transition *> allTransitions();
  virtual void prepareRun();
  void setTape(Tape *);
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
