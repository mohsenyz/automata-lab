#ifndef TAPEDRAWABLE_H
#define TAPEDRAWABLE_H

#include "tape.h"
#include <QGraphicsItem>

namespace AutomataLab {
class TapeDrawable : public QObject, public Tape, public QGraphicsItem {
  Q_OBJECT
public:
  explicit TapeDrawable(QString);
  int type() const override;
  QRectF boundingRect() const override;
  void moveRight() override;
  void moveLeft() override;
  void write(QChar) override;
  bool isLocked();
  void setLocked(bool locked);

signals:
  void headMoved(QPointF);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  bool _isLocked;
};

} // namespace AutomataLab
#endif // TAPEDRAWABLE_H
