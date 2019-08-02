#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "inspectorlayout.h"
#include "machine.h"
#include "multiplerunlayout.h"
#include "tapedrawable.h"
#include "turingmachinescene.h"
#include "ui_mainwindow.h"
#include <QMainWindow>

namespace AutomataLab {
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  explicit MainWindow(QString fileName, QWidget *parent = nullptr);
  void init();
public slots:
  void on_newStateBtn_clicked();
  void on_moveBtn_clicked();
  void requestSelect();
  void transitionInserted(Transition *transition);
  void transitionEditRule(Transition *transition);
  void stateEditLabel(State *state);
  void stateSelected(State *);
  void stateUnselected();
  void headMoved(QPointF);
  void stateSetInitial(StateDrawable *);
  void on_newTransitionBtn_clicked();
  void uncheckToolBtns();
  void on_setInputBtn_clicked();
  void on_fastRunBtn_clicked();
  void on_nextStepBtn_clicked();
  void on_file_newAction();
  void on_file_openAction();
  void on_file_saveAction();
  void on_file_saveAsAction();
  void on_file_saveAsImageAction();

private:
  QString saveFileName = "";
  bool isRunning;
  void createToolboxPanels();
  void clearRuntimeEnvironment();
  InspectorLayout *inspectorLayout;
  MultipleRunLayout *multipleRunLayout;
  Ui::MainWindow *ui;
  AutomataScene *automataScene;
  QGraphicsScene *tapeScene;
  TapeDrawable *tapeDrawable = nullptr;
};
} // namespace AutomataLab

#endif // MAINWINDOW_H
