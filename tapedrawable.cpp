#include "tapedrawable.h"
#include "QPainter"
#include "automatascene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <cmath>
using namespace AutomataLab;

TapeDrawable::TapeDrawable(QString input) : Tape(input) {}

int TapeDrawable::type() const { return AutomataScene::ItemType::TapeItem; }

QRectF TapeDrawable::boundingRect() const {
  return QRectF(QPointF(0, 0), QSizeF(50 * tape.size(), 50));
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
  painter->setPen(QPen(QBrush(Qt::black), borderWidth));
  for (unsigned int i = 0; i < tape.size(); i++) {
    auto block = tape[i];
    QRectF rect(QPointF(startWidth, 0), QSizeF(blockWidth, blockHeight));
    if (i == currentIndex) {
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

void TapeDrawable::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  double xPos = event->scenePos().x();
  currentIndex = floor(xPos / 50.0);
  emit headMoved(QPointF(currentIndex * 50 + 25, 0));
  update();
}
