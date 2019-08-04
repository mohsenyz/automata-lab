#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "inspectorlayout.h"
#include "machine.h"
#include "multiplerunlayout.h"
#include "tapedrawable.h"
#include "turingmachinescene.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QNetworkAccessManager>

namespace AutomataLab {
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;
  void resizeEvent(QResizeEvent *event) override;
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
  void on_file_saveAsPdf();
  void loadSavedAutomata();
  void on_file_saveAsImageAction();
  void on_help_productActivationAction();
  void onActivationResultReceived(QNetworkReply *);

private slots:
  void on_newComponentBtn_clicked();

private:
  int numOfComponents = 1;
  QString saveFileName = "";
  bool isRunning;
  QNetworkAccessManager *manager;
  void createToolboxPanels();
  void clearRuntimeEnvironment();
  void askForMachineType();
  void initWindowTitle();
  void initViews();
  void initObservers();
  QJsonObject jsonObject;
  InspectorLayout *inspectorLayout;
  MultipleRunLayout *multipleRunLayout;
  Ui::MainWindow *ui;
  AutomataScene *automataScene;
  QGraphicsScene *tapeScene;
  TapeDrawable *tapeDrawable = nullptr;
};
} // namespace AutomataLab

#endif // MAINWINDOW_H
