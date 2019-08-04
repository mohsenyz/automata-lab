#ifndef INSPECTORLAYOUT_H
#define INSPECTORLAYOUT_H
#include "statedrawable.h"
#include <QCheckBox>
#include <QLabel>
#include <QToolBox>
#include <QWidget>

namespace AutomataLab {

/**
 * @brief The InspectorLayout class, Inspects selected state, support editing
 * state
 */
class InspectorLayout : public QWidget {
  Q_OBJECT
public:
  /**
   * @brief InspectorLayout
   */
  InspectorLayout(QWidget *);

  /**
   * @brief Sets state drawable to be inspected
   */
  void setState(StateDrawable *);

  /**
   * @brief Returns currently inspecting state
   * @return
   */
  StateDrawable *state();

  /**
   * @brief Returns inspector index in toolwindow
   * @return
   */
  int index();

  /**
   * @brief Focues on inspector layout
   */
  void focus();

  /**
   * @brief Atteches inspector window to toolwindow
   * @param box
   */
  void attach(QToolBox *box);

  /**
   * @brief Detaches inspector from ui
   */
  void detach();

  /**
   * @brief Check is inspector attached to toolwindow
   * @return
   */
  bool isAttached();

  /**
   * @brief Invalidates inspector layout
   */
  void invalidate();

public slots:
  /**
   * @brief initialCheckboxStateChanged, called when user toggles initial
   * checkbox
   */
  void initialCheckboxStateChanged(int);

  /**
   * @brief finalCheckboxStateChanged, called when user toggles final checkbox
   */
  void finalCheckboxStateChanged(int);

signals:
  /**
   * @brief stateSetInitial, emits when state set to initial, in order to check
   * for multiple initial state error
   */
  void stateSetInitial(StateDrawable *);

private:
  StateDrawable *_state = nullptr;
  int _index;
  QToolBox *box = nullptr;
  QLabel *stateName;
  QCheckBox *initialCheckbox;
  QCheckBox *finalCheckbox;
};

} // namespace AutomataLab

#endif // INSPECTORLAYOUT_H
