#ifndef TRANSITIONDRAWABLE_H
#define TRANSITIONDRAWABLE_H

#include "serializable.h"
#include "statedrawable.h"
#include "turingtransition.h"
#include <QGraphicsLineItem>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>

namespace AutomataLab {

class TransitionDrawable : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
public:
  TransitionDrawable();
  ~TransitionDrawable();
  int type() const override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void updatePosition();
  QColor lineColor();
  int curve();
  void setCurve(int);
  void setLineColor(QColor);
  virtual QString getBoxLabel() = 0;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0) override;

protected:
  void setLine(QLineF);
  QLineF line() const;
  Transition *transition();
  int _curve = 0;
  QLineF _line;
  QColor _lineColor;
  QPolygonF arrowHead;
  QPainterPath _linePath;
  Transition *_transition;
};

} // namespace AutomataLab

#endif // TRANSITIONDRAWABLE_H
