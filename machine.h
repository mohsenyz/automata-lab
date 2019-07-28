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
  virtual void prepareRun();
  void setTape(Tape *);
  Tape *tape();
  void virtual nextStep() = 0;
  Transition *nextTransition();
  State *currentState();
  virtual int type() = 0;
  virtual bool isHalted() = 0;
  virtual bool isAccepted() = 0;
  virtual bool run() = 0;

private:
  std::vector<State *> states;
  std::vector<Transition *> transitions;
  Tape *_tape;
  State *_currentState;

protected:
  void setCurrentState(State *);
};

} // namespace AutomataLab

#endif // MACHINE_H
