#ifndef AUTOMATASCENE_H
#define AUTOMATASCENE_H
#include "machine.h"
#include "statedrawable.h"
#include "transitiondrawable.h"
#include <QFile>
#include <QGraphicsScene>
namespace AutomataLab {

/**
 * @brief The AutomataScene class, Contains the graphical automata machine
 */
class AutomataScene : public QGraphicsScene {
  Q_OBJECT
public:
  /**
   * @brief The ItemType enum, Type of machine
   */
  enum ItemType { StateItem, TransitionItem, TapeItem };

  /**
   * @brief The Mode enum, Current mode of machine
   * InsertTransition -> User is inserting a transition
   * InsertState -> User is inserting a state
   * Select -> User is just moving  items, or doing nothing!
   */
  enum Mode { InsertTransition, InsertState, Select };

  /**
   * @brief AutomataScene, Creates a machine scene with specific machine type
   * @param parent
   */
  AutomataScene(QObject *parent, MachineType);

  /**
   * @brief Returns current machine type
   * @return
   */
  virtual MachineType machineType() const;

  /**
   * @brief Sets current machine type
   * @return
   */
  Mode currentMode() const;

  /**
   * @brief Sets current automata mode
   */
  void setCurrentMode(Mode);

  /**
   * @brief Saves automata into a file
   */
  void saveTo(QString);

  /**
   * @brief loads an automata from a json file, and adds it to current machine.
   * States will have a prefix
   * @param statePrefix
   */
  void loadFromJson(QJsonObject, QString statePrefix = "",
                    bool disableStartState = false);

  /**
   * @brief Adds state to an automata
   */
  void addState(StateDrawable *, QPointF);

  /**
   * @brief Adds transition to an automata
   * @param transition
   */
  void addTransition(TransitionDrawable *transition);

  /**
   * @brief Removes a transition from automata
   * @param transition
   */
  void removeTransition(TransitionDrawable *transition);

  /**
   * @brief Removes state from automata
   * @param state
   */
  void removeState(StateDrawable *state);

signals:
  /**
   * @brief Requests select, adding state or transition will be rejected
   */
  void requestSelect();

  /**
   * @brief Called when transition inserted
   * @param transition
   */
  void transitionInserted(Transition *transition);

  /**
   * @brief Called when user requests editing transition rule
   * @param transition
   */
  void transitionEditRule(Transition *transition);

  /**
   * @brief Called when user requests editing state
   * @param state
   */
  void stateEditLabel(State *state);

  /**
   * @brief Called when state selected, used to show state inspector
   */
  void stateSelected(State *);

  /**
   * @brief Called when state unselected, used to hide/disable inspector
   */
  void stateUnselected();

protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void keyPressEvent(QKeyEvent *keyEvent) override;

private:
  Mode _currentMode = Mode::Select;
  MachineType _machineType;
  /**
   * @brief Recurves transtion, So transition between two specific states, won't
   * intersect
   * @param fromState
   * @param toState
   */
  void recurveTransitions(State *fromState, State *toState);
  QGraphicsLineItem *tempLine = nullptr;
};

} // namespace AutomataLab
#endif // AUTOMATASCENE_H
