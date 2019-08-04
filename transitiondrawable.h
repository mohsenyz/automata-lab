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

/**
 * @brief The TransitionDrawable class, Draws transition
 */
class TransitionDrawable : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
public:
  /**
   * @brief TransitionDrawable
   */
  TransitionDrawable();
  ~TransitionDrawable();
  int type() const override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

  /**
   * @brief Updates transition location
   */
  void updatePosition();

  /**
   * @brief Returns line color
   * @return
   */
  QColor lineColor();

  /**
   * @brief Returns live curve
   * @return
   */
  int curve();

  /**
   * @brief Sets line curve
   */
  void setCurve(int);

  /**
   * @brief Sets line color
   */
  void setLineColor(QColor);
  virtual QString getBoxLabel() = 0;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0) override;

protected:
  /**
   * @brief Sets straight line from state to state
   */
  void setLine(QLineF);

  /**
   * @brief Returns straight line from state to state
   * @return
   */
  QLineF line() const;

  /**
   * @brief Returns transition class
   * @return
   */
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
