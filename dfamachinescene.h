#ifndef DFAMACHINESCENE_H
#define DFAMACHINESCENE_H

#include "automatascene.h"
#include "dfamachine.h"
#include "dfatransitiondrawable.h"
#include "statedrawable.h"

namespace AutomataLab {

/**
 * @brief The DFAMachineScene class
 */
class DFAMachineScene : public AutomataScene, public DFAMachine {
  Q_OBJECT
public:
  DFAMachineScene(QObject *parent);
};

} // namespace AutomataLab

#endif // DFAMACHINESCENE_H
