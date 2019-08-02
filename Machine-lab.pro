#-------------------------------------------------
#
# Project created by QtCreator 2019-07-12T16:02:12
#
#-------------------------------------------------

QT       += core gui
QT       += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Machine-lab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 testcase

SOURCES += \
        automatascene.cpp \
        dfamachine.cpp \
        dfamachine_test.cpp \
        dfamachinescene.cpp \
        dfatransition.cpp \
        dfatransitiondrawable.cpp \
        inspectorlayout.cpp \
        machine.cpp \
        main.cpp \
        mainwindow.cpp \
        multiplerunlayout.cpp \
        state.cpp \
        statedrawable.cpp \
        tape.cpp \
        tapedrawable.cpp \
        testsuite.cpp \
        tape_test.cpp \
        transition.cpp \
        turingmachine.cpp \
        turingmachine_test.cpp \
        turingmachinescene.cpp \
        turingtransition.cpp \
        turingtransitiondrawable.cpp \
        ui_utils.cpp

HEADERS += \
        automatascene.h \
        dfamachine.h \
        dfamachine_test.h \
        dfamachinescene.h \
        dfatransition.h \
        dfatransitiondrawable.h \
        inspectorlayout.h \
        machine.h \
        mainwindow.h \
        multiplerunlayout.h \
        state.h \
        statedrawable.h \
        tape.h \
        tapedrawable.h \
        testsuite.h \
        tape_test.h \
        transition.h \
        turingmachine.h \
        turingmachine_test.h \
        turingmachinescene.h \
        turingtransition.h \
        turingtransitiondrawable.h \
        ui_utils.h

FORMS += \
        mainwindow.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
