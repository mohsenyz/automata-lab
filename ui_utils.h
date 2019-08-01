#ifndef UI_UTILS_H
#define UI_UTILS_H

#include "dfamachinescene.h"
#include "dfatransitiondrawable.h"
#include "statedrawable.h"
#include "turingmachinescene.h"
#include "turingtransitiondrawable.h"
#include <QGraphicsDropShadowEffect>

QGraphicsDropShadowEffect *state_default_shadow_effect();

#define DRAWABLE_STATE(state) (dynamic_cast<StateDrawable *>(state))

#define DRAWABLE_TURING_TRANSITION(state)                                      \
  (dynamic_cast<TuringTransitionDrawable *>(state))

#define SCENE_TURING_MACHINE(scene) (dynamic_cast<TuringMachineScene *>(scene))

#define SCENE_DFA_MACHINE(scene) (dynamic_cast<DFAMachineScene *>(scene))

#define SCENE_MACHINE(scene) (dynamic_cast<Machine *>(scene))

#define DRAWABLE_DFA_TRANSITION(state)                                         \
  (dynamic_cast<DFATransitionDrawable *>(state))

#endif // UI_UTILS_H
