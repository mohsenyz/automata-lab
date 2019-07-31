#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "inspectorlayout.h"
#include "machine.h"
#include "turingmachinescene.h"
#include "ui_mainwindow.h"
#include <QMainWindow>

namespace AutomataLab {
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_newStateBtn_clicked();
  void on_moveBtn_clicked();
  void requestSelect();
  void transitionInserted(Transition *transition);
  void transitionEditRule(Transition *transition);
  void stateEditLabel(State *state);
  void stateSelected(State *);

  void on_newTransitionBtn_clicked();
  void uncheckToolBtns();

private:
  void createToolboxPanels();
  InspectorLayout *inspectorLayout;
  Ui::MainWindow *ui;
};
} // namespace AutomataLab

#endif // MAINWINDOW_H
