#include "dfatransitiondrawable.h"
#include "ui_utils.h"
using namespace AutomataLab;

#include <cmath>
#include <qmath.h>

DFATransitionDrawable::DFATransitionDrawable(StateDrawable *startState,
                                             StateDrawable *endState,
                                             std::vector<QChar> acceptedInputs)
    : DFATransition(startState, endState, acceptedInputs), QGraphicsItem() {
  setZValue(5);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setLineColor(Qt::black);
}

DFATransitionDrawable::DFATransitionDrawable(StateDrawable *startState,
                                             StateDrawable *endState,
                                             QChar acceptedInput)
    : DFATransition(startState, endState, acceptedInput), QGraphicsItem() {
  setZValue(5);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setLineColor(Qt::black);
}

int DFATransitionDrawable::type() const {
  return AutomataScene::ItemType::TransitionItem;
}

QRectF DFATransitionDrawable::boundingRect() const {
  qreal extra = 4;
  return _linePath.boundingRect().normalized().adjusted(-extra, -extra, extra,
                                                        extra);
}

QPainterPath DFATransitionDrawable::shape() const { return _linePath; }

void DFATransitionDrawable::updatePosition() {
  QLineF line(mapFromItem(DRAWABLE_STATE(fromState()), 0, 0),
              mapFromItem(DRAWABLE_STATE(toState()), 0, 0));
  setLine(line);
}

void DFATransitionDrawable::paint(QPainter *painter,
                                  const QStyleOptionGraphicsItem *option,
                                  QWidget *) {
  if (DRAWABLE_STATE(fromState())
          ->collidesWithItem(DRAWABLE_STATE(toState())) &&
      !(*fromState() == *toState()))
    return;
  QString labelText = QString(acceptInputs()[0]);
  QColor color = lineColor();
  if (option->state & QStyle::State_Selected) {
    color = QColor(0, 151, 167);
  }
  QPen myPen;
  myPen.setWidth(4);
  myPen.setColor(color);
  qreal arrowSize = 15;
  painter->setPen(myPen);
  painter->setBrush(color);

  auto fromPoint = DRAWABLE_STATE(fromState())->pos() +
                   DRAWABLE_STATE(fromState())->boundingRect().center();
  auto toPoint = DRAWABLE_STATE(toState())->pos() +
                 DRAWABLE_STATE(toState())->boundingRect().center();

  if (*fromState() == *toState()) {
    int width = 100 + curve() * 30;
    _linePath = QPainterPath();
    QRectF rect = QRectF(fromPoint - QPointF(width / 2, width - 20),
                         QSizeF(width, width));
    QPainterPathStroker stroker;
    stroker.setWidth(3);
    _linePath.arcTo(rect, 0, 360 * 16);
    _linePath = stroker.createStroke(_linePath);
    painter->drawArc(rect, 0, 360 * 16);
    QRectF textRect(rect.center() - QPointF(40, rect.height() / 2),
                    QSizeF(80, 20));
    painter->drawRect(textRect);
    painter->setPen(Qt::white);
    painter->drawText(textRect, labelText,
                      QTextOption(Qt::AlignmentFlag::AlignCenter));

    _linePath.addRect(rect);
    return;
  }

  QLineF centerLine(fromPoint, toPoint);
  centerLine.setLength(centerLine.length() - 55);

  setLine(centerLine);

  QLineF smallLine = line();
  smallLine.setLength(smallLine.length() + 55);
  _linePath = QPainterPath();
  _linePath.moveTo(smallLine.p1());
  QLineF normalLine;
  normalLine.setP1(smallLine.center());
  normalLine.setAngle(smallLine.normalVector().angle());
  normalLine.setLength(60 * curve());
  _linePath.quadTo(normalLine.p2(), smallLine.p2());
  QPainterPathStroker stroker;
  stroker.setWidth(0);
  QPainterPath backup = _linePath;
  _linePath = stroker.createStroke(_linePath);
  painter->drawPath(_linePath);

  QLineF arrowLine(backup.pointAtPercent(0.95), smallLine.p2());
  double angle = std::atan2(arrowLine.dy(), -arrowLine.dx());
  QPointF p2 =
      backup.pointAtPercent(1 - backup.toReversed().percentAtLength(50));

  QPointF arrowP1 = p2 + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                 cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 = p2 + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                 cos(angle + M_PI - M_PI / 3) * arrowSize);

  arrowHead.clear();
  arrowHead << p2 << arrowP1 << arrowP2;

  painter->drawPolygon(arrowHead);
  normalLine.setLength(30 * abs(curve()));
  QRectF textRect(normalLine.p2() - QPointF(40, 10), QSizeF(80, 20));
  _linePath.addRect(textRect);
  _linePath.addPolygon(arrowHead);
  painter->drawRect(textRect);
  painter->setPen(Qt::white);
  painter->drawText(textRect, labelText,
                    QTextOption(Qt::AlignmentFlag::AlignCenter));
}

void DFATransitionDrawable::setLine(QLineF line) { _line = line; }

QLineF DFATransitionDrawable::line() const { return _line; }

void DFATransitionDrawable::setLineColor(QColor lineColor) {
  _lineColor = lineColor;
  update();
}

void DFATransitionDrawable::setCurve(int curve) { _curve = curve; }

int DFATransitionDrawable::curve() { return _curve; }

void DFATransitionDrawable::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  update();
  QGraphicsItem::mousePressEvent(event);
}

void DFATransitionDrawable::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  update();
  QGraphicsItem::mouseMoveEvent(event);
}

QColor DFATransitionDrawable::lineColor() { return _lineColor; }
