#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <QGraphicsDropShadowEffect>

QGraphicsDropShadowEffect *state_default_shadow_effect() {
  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
  effect->setColor(QColor(30, 30, 30));
  effect->setBlurRadius(15);
  effect->setOffset(0, 0);
  return effect;
}

#endif // UI_UTILS_H
