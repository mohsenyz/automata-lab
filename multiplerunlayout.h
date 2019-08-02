#ifndef MULTIPLERUNLAYOUT_H
#define MULTIPLERUNLAYOUT_H

#include "machine.h"
#include <QCheckBox>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QToolBox>
#include <QWidget>

namespace AutomataLab {

class MultipleRunLayout : public QWidget {
  Q_OBJECT
public:
  MultipleRunLayout(QWidget *, Machine *machine);
  void setMachine(Machine *);

  int index();
  void focus();
  void attach(QToolBox *box);
  void detach();
  bool isAttached();

private slots:
  void on_runBtn_clicked();
  void on_addRowBtn_clicked();
  void on_removeSelectedBtn_clicked();
  void on_tableSelection_changed();
  void on_tableCell_changed(int, int);

private:
  QToolBox *box = nullptr;
  Machine *_machine = nullptr;
  QPushButton *removeSelectedBtn;
  QTableWidget *tableWidget;
  int _index;
};

} // namespace AutomataLab

#endif // MULTIPLERUNLAYOUT_H
