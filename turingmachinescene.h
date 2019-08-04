#ifndef TURINGMACHINESCENE_H
#define TURINGMACHINESCENE_H

#include "automatascene.h"
#include "statedrawable.h"
#include "turingmachine.h"
#include "turingtransitiondrawable.h"

namespace AutomataLab {

/**
 * @brief The TuringMachineScene class
 */
class TuringMachineScene : public AutomataScene, public TuringMachine {
  Q_OBJECT
public:
  TuringMachineScene(QObject *parent);
};

} // namespace AutomataLab

#endif // TURINGMACHINESCENE_H
