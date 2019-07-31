#ifndef INSPECTORLAYOUT_H
#define INSPECTORLAYOUT_H
#include "statedrawable.h"
#include <QCheckBox>
#include <QLabel>
#include <QToolBox>
#include <QWidget>

namespace AutomataLab {

class InspectorLayout : public QWidget {
  Q_OBJECT
public:
  InspectorLayout(QWidget *);
  void setState(StateDrawable *);
  StateDrawable *state();

  int index();
  void focus();
  void attach(QToolBox *box);
  void detach();
  bool isAttached();
  void invalidate();

public slots:
  void initialCheckboxStateChanged(int);
  void finalCheckboxStateChanged(int);

signals:
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
