#include "tapedrawable.h"
#include "QPainter"
#include "automatascene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <cmath>
using namespace AutomataLab;

TapeDrawable::TapeDrawable(QString input, MachineType machineType)
    : Tape(input), _machineType(machineType) {}

int TapeDrawable::type() const { return AutomataScene::ItemType::TapeItem; }

QRectF TapeDrawable::boundingRect() const {
  int tapeSize = _machineType == DFA ? inputSize() : tape.size();
  return QRectF(QPointF(0, 0), QSizeF(50 * tapeSize, 50));
}

void TapeDrawable::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  QFont font = painter->font();
  font.setPixelSize(24);
  font.setBold(true);
  painter->setFont(font);
  int startWidth = 0;
  const int blockWidth = 50;
  const int blockHeight = 50;
  const int borderWidth = 3;
  int tapeSize = _machineType == DFA ? inputSize() : tape.size();
  painter->setPen(QPen(QBrush(Qt::black), borderWidth));
  for (unsigned int i = 0; i < tapeSize; i++) {
    auto block = tape[i];
    QRectF rect(QPointF(startWidth, 0), QSizeF(blockWidth, blockHeight));
    if (i == currentIndex()) {
      painter->setPen(QPen(QBrush(QColor(255, 193, 7)), borderWidth));
      QRectF ellipseRect = rect;
      ellipseRect.setSize(rect.size() - QSizeF(10, 10));
      ellipseRect.translate(5, 5);
      painter->drawEllipse(ellipseRect);
      painter->setPen(QPen(QBrush(Qt::black), borderWidth));
    } else {
      painter->setPen(QPen(QBrush(Qt::black), borderWidth));
    }
    painter->drawRect(rect);
    painter->drawText(rect, block, QTextOption(Qt::AlignmentFlag::AlignCenter));
    startWidth += blockWidth;
  }
}

void TapeDrawable::write(QChar character) {
  Tape::write(character);
  update();
}

void TapeDrawable::moveRight() {
  Tape::moveRight();
  update();
}

void TapeDrawable::moveLeft() {
  Tape::moveLeft();
  update();
}

bool TapeDrawable::isLocked() { return _isLocked; }

void TapeDrawable::setLocked(bool locked) { _isLocked = locked; }

void TapeDrawable::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (isLocked())
    return;
  double xPos = event->scenePos().x();
  _currentIndex = floor(xPos / 50.0);
  emit headMoved(QPointF(_currentIndex * 50 + 25, 0));
  update();
}
