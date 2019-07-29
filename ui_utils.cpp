#include "ui_utils.h"

QGraphicsDropShadowEffect *state_default_shadow_effect() {
  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
  effect->setColor(QColor(30, 30, 30));
  effect->setBlurRadius(15);
  effect->setOffset(0, 0);
  return effect;
}
