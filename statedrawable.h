#ifndef STATEDRAWABLE_H
#define STATEDRAWABLE_H

#include "state.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace AutomataLab {

class StateDrawable : public QObject, public State, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(
      QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
public:
  StateDrawable(QString label);
  virtual ~StateDrawable();
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
  int type() const;
  QColor backgroundColor() const;
  void setBackgroundColor(QColor color);

  QColor borderColor() const;
  void setBorderColor(QColor color);

private:
  QColor _backgroundColor;
  QColor _borderColor;
  QGraphicsDropShadowEffect *shadowEffect;

protected:
  // overriding mouse events
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
}; // namespace AutomataLab

#endif // STATEDRAWABLE_H
