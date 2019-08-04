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

/**
 * @brief The MultipleRunLayout class, Runs multiple input and shows input
 */
class MultipleRunLayout : public QWidget {
  Q_OBJECT
public:
  /**
   * @brief MultipleRunLayout
   * @param machine
   */
  MultipleRunLayout(QWidget *, Machine *machine);

  /**
   * @brief Sets machine to run inputs
   */
  void setMachine(Machine *);

  /**
   * @brief Returns layout index in toolwindow
   * @return
   */
  int index();

  /**
   * @brief Focuses in multiple run window
   */
  void focus();

  /**
   * @brief Attaches layout to toolwindow
   * @param box
   */
  void attach(QToolBox *box);

  /**
   * @brief Detach layout from toolwindow
   */
  void detach();

  /**
   * @brief Check is layout attached to toolwindow
   * @return
   */
  bool isAttached();

private slots:

  /**
   * @brief Calles when run btn clicked
   */
  void on_runBtn_clicked();

  /**
   * @brief Calles when add row btn clicked
   */
  void on_addRowBtn_clicked();

  /**
   * @brief Calles when remove selected btn clicked
   */
  void on_removeSelectedBtn_clicked();

  /**
   * @brief Calles when user select/unselect rows
   */
  void on_tableSelection_changed();

  /**
   * @brief Calles when user changes a cell
   */
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
