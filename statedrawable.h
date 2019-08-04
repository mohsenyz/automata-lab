#ifndef STATEDRAWABLE_H
#define STATEDRAWABLE_H

#include "state.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace AutomataLab {

/**
 * @brief The StateDrawable class, Contains drawable state
 */
class StateDrawable : public QObject, public State, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(
      QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
public:
  /**
   * @brief StateDrawable
   */
  StateDrawable();

  /**
   * @brief StateDrawable with label
   * @param label
   */
  StateDrawable(QString label);
  virtual ~StateDrawable() override;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  int type() const override;

  /**
   * @brief Returns state background color
   * @return
   */
  QColor backgroundColor() const;

  /**
   * @brief Sets state background state
   * @param color
   */
  void setBackgroundColor(QColor color);

  /**
   * @brief Returns border color
   * @return
   */
  QColor borderColor() const;

  /**
   * @brief Sets border color
   * @param color
   */
  void setBorderColor(QColor color);

  virtual void readJson(QJsonObject &) override;
  virtual void writeJson(QJsonObject &) override;

private:
  /**
   * @brief inits view
   */
  void init();
  QColor _backgroundColor;
  QColor _borderColor;
  QGraphicsDropShadowEffect *shadowEffect;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
}; // namespace AutomataLab

#endif // STATEDRAWABLE_H
