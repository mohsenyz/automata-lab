#include "statedrawable.h"
#include "automatascene.h"
#include "ui_utils.h"

using namespace AutomataLab;

StateDrawable::StateDrawable(QString label) : State(label) {
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

  setBorderColor(QColor(0, 151, 167));
  setBackgroundColor(QColor(0, 188, 212));
  shadowEffect = state_default_shadow_effect();
  setGraphicsEffect(shadowEffect);
  setZValue(10);
}

StateDrawable::~StateDrawable() {}

void StateDrawable::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
  if (option->state & QStyle::State_Selected) {
    shadowEffect->setEnabled(true);
  } else {
    shadowEffect->setEnabled(false);
  }
  QRectF rect = boundingRect();
  QPen pen(borderColor(), 3);
  painter->setPen(pen);
  painter->setBrush(backgroundColor());
  painter->drawEllipse(rect);

  if (isFinal()) {
    QRectF innerRect = rect;
    innerRect.setSize(rect.size() - QSizeF(16, 16));
    innerRect.translate(8, 8);
    painter->drawArc(innerRect, 0, 360 * 16);
  }

  QFont font = painter->font();
  font.setPointSize(font.pointSize() * 1.7);
  painter->setFont(font);
  QPen fontPen(Qt::white, 3);
  painter->setPen(fontPen);
  painter->drawText(rect, label(), QTextOption(Qt::AlignmentFlag::AlignCenter));
}

QRectF StateDrawable::boundingRect() const { return QRectF(0, 0, 100, 100); }

QColor StateDrawable::borderColor() const { return _borderColor; }

void StateDrawable::setBorderColor(QColor borderColor) {
  _borderColor = borderColor;
  update();
}

QColor StateDrawable::backgroundColor() const { return _backgroundColor; }

void StateDrawable::setBackgroundColor(QColor backgroundColor) {
  _backgroundColor = backgroundColor;
  update();
}

int StateDrawable::type() const { return AutomataScene::ItemType::StateItem; }

void StateDrawable::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  update();
  QGraphicsItem::mousePressEvent(event);
}

void StateDrawable::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}
