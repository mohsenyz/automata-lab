#ifndef DFATRANSITIONDRAWABLE_H
#define DFATRANSITIONDRAWABLE_H

#include "automatascene.h"
#include "dfatransition.h"
#include "statedrawable.h"
#include <QGraphicsLineItem>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>

namespace AutomataLab {

class DFATransitionDrawable : public QObject,
                              public DFATransition,
                              public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
public:
  DFATransitionDrawable(StateDrawable *, StateDrawable *, std::vector<QChar>);

  DFATransitionDrawable(StateDrawable *, StateDrawable *, QChar);

  int type() const override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void updatePosition();
  QColor lineColor();
  int curve();
  void setCurve(int);
  void setLineColor(QColor);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0) override;

private:
  void setLine(QLineF);
  QLineF line() const;
  int _curve = 0;
  QLineF _line;
  QColor _lineColor;
  QPolygonF arrowHead;
  QPainterPath _linePath;
};

} // namespace AutomataLab

#endif // DFATRANSITIONDRAWABLE_H
