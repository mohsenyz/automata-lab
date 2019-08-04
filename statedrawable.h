#ifndef STATEDRAWABLE_H
#define STATEDRAWABLE_H

#include "state.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace AutomataLab {

class StateDrawable : public QObject, public State, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(
      QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
public:
  StateDrawable();
  StateDrawable(QString label);
  virtual ~StateDrawable();
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  int type() const override;
  QColor backgroundColor() const;
  void setBackgroundColor(QColor color);

  QColor borderColor() const;
  void setBorderColor(QColor color);
  virtual void readJson(QJsonObject &) override;
  virtual void writeJson(QJsonObject &) override;

private:
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
