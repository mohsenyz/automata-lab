#ifndef TAPEDRAWABLE_H
#define TAPEDRAWABLE_H

#include "automatascene.h"
#include "tape.h"
#include <QGraphicsItem>

namespace AutomataLab {

/**
 * @brief The TapeDrawable class
 */
class TapeDrawable : public QObject, public Tape, public QGraphicsItem {
  Q_OBJECT
public:
  /**
   * @brief TapeDrawable
   * @param type
   */
  explicit TapeDrawable(QString, MachineType type);
  int type() const override;
  QRectF boundingRect() const override;
  void moveRight() override;
  void moveLeft() override;
  void write(QChar) override;

  /**
   * @brief Returns true if tape is locked
   * @return
   */
  bool isLocked();

  /**
   * @brief Locks tape from changing head, Used during machine runtime
   * @return
   */
  void setLocked(bool locked);

signals:
  /**
   * @brief emits when head moves
   */
  void headMoved(QPointF);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  bool _isLocked;
  MachineType _machineType;
};

} // namespace AutomataLab
#endif // TAPEDRAWABLE_H
