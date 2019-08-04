#include "dfamachinescene.h"
#include "statedrawable.h"
#include "ui_utils.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <cmath>
using namespace AutomataLab;

DFAMachineScene::DFAMachineScene(QObject *parent)
    : AutomataScene(parent, DFA) {}
