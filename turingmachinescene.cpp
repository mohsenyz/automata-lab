#include "turingmachinescene.h"
#include "statedrawable.h"
#include "ui_utils.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <cmath>
using namespace AutomataLab;

TuringMachineScene::TuringMachineScene(QObject *parent)
    : AutomataScene(parent, TURING) {}
