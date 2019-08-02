#include "ui_utils.h"
#include <boost/foreach.hpp>

QGraphicsDropShadowEffect *state_default_shadow_effect() {
  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
  effect->setColor(QColor(30, 30, 30));
  effect->setBlurRadius(15);
  effect->setOffset(0, 0);
  return effect;
}

QString getNewStateName(Machine *machine) {
  QString alphabet = "pabcdefghijklmnoqrstuvwxyz";
  for (int i = 0; i < alphabet.size(); i++) {
    for (int j = 0; j < 100; j++) {
      if (machine->stateByLabel(alphabet[i].toUpper() + QString::number(j)) ==
          nullptr) {
        return alphabet[i].toUpper() + QString::number(j);
      }
    }
  }
  return "WTF";
}
