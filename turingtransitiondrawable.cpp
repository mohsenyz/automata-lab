#include "turingtransitiondrawable.h"
#include "ui_utils.h"
using namespace AutomataLab;

#include <cmath>
#include <qmath.h>

TuringTransitionDrawable::TuringTransitionDrawable(
    StateDrawable *startState, StateDrawable *endState,
    std::vector<QChar> acceptedInputs, QChar write, Direction direction,
    QGraphicsItem *parent)
    : TuringTransition(startState, endState, acceptedInputs, write, direction),
      QGraphicsLineItem(parent) {
  setZValue(5);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setLineColor(Qt::black);
}

TuringTransitionDrawable::TuringTransitionDrawable(
    StateDrawable *startState, StateDrawable *endState, QChar acceptedInput,
    QChar write, Direction direction, QGraphicsItem *parent)
    : TuringTransition(startState, endState, acceptedInput, write, direction),
      QGraphicsLineItem(parent) {
  setZValue(5);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setLineColor(Qt::black);
}

int TuringTransitionDrawable::type() const {
  return AutomataScene::ItemType::Transition;
}

QRectF TuringTransitionDrawable::boundingRect() const {
  qreal extra = (pen().width() + 20) / 2.0;
  return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                    line().p2().y() - line().p1().y()))
      .normalized()
      .adjusted(-extra, -extra, extra, extra);
}

QPainterPath TuringTransitionDrawable::shape() const {
  QPainterPath path = QGraphicsLineItem::shape();
  path.addPolygon(arrowHead);
  return path;
}

void TuringTransitionDrawable::updatePosition() {
  QLineF line(mapFromItem(DRAWABLE_STATE(fromState()), 0, 0),
              mapFromItem(DRAWABLE_STATE(toState()), 0, 0));
  setLine(line);
}

void TuringTransitionDrawable::paint(QPainter *painter,
                                     const QStyleOptionGraphicsItem *option,
                                     QWidget *) {
  if (DRAWABLE_STATE(fromState())->collidesWithItem(DRAWABLE_STATE(toState())))
    return;
  QColor color = lineColor();
  QPen myPen = pen();
  myPen.setWidth(2);
  myPen.setColor(color);
  qreal arrowSize = 15;
  painter->setPen(myPen);
  painter->setBrush(color);

  auto fromPoint = DRAWABLE_STATE(fromState())->pos() +
                   DRAWABLE_STATE(fromState())->boundingRect().center();
  auto toPoint = DRAWABLE_STATE(toState())->pos() +
                 DRAWABLE_STATE(toState())->boundingRect().center();

  QLineF centerLine(fromPoint, toPoint);
  centerLine.setLength(centerLine.length() - 55);

  setLine(centerLine);

  double angle = std::atan2(line().dy(), -line().dx());

  QPointF arrowP1 = line().p2() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                          cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 =
      line().p2() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                            cos(angle + M_PI - M_PI / 3) * arrowSize);

  arrowHead.clear();
  arrowHead << line().p2() << arrowP1 << arrowP2;
  painter->drawLine(line());
  painter->drawPolygon(arrowHead);
  QRectF textRect(QPointF(line().center()) - QPointF(40, 10), QSizeF(80, 20));
  painter->drawRect(textRect);
  painter->setPen(Qt::white);
  painter->drawText(textRect, "Test",
                    QTextOption(Qt::AlignmentFlag::AlignCenter));
}

void TuringTransitionDrawable::setLineColor(QColor lineColor) {
  _lineColor = lineColor;
}

QColor TuringTransitionDrawable::lineColor() { return _lineColor; }
