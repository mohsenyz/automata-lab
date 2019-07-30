#ifndef TAPEDRAWABLE_H
#define TAPEDRAWABLE_H

#include "tape.h"
#include <QGraphicsItem>

namespace AutomataLab {
class TapeDrawable : public QObject, public Tape, public QGraphicsItem {
  Q_OBJECT
public:
  explicit TapeDrawable(QString);
  //  int type() const override;
  //  QRectF boundingRect() const override;

  // protected:
  //  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
  //             QWidget *widget = 0) override;
  //  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace AutomataLab
#endif // TAPEDRAWABLE_H
