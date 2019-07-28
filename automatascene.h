#ifndef AUTOMATASCENE_H
#define AUTOMATASCENE_H

#include <QGraphicsScene>

namespace AutomataLab {

class AutomataScene : public QGraphicsScene {

public:
  enum ItemTypes { State, Transition };
  AutomataScene(QObject *parent);
};

} // namespace AutomataLab
#endif // AUTOMATASCENE_H
