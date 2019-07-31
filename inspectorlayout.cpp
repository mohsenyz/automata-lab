#include "inspectorlayout.h"
#include <QSpacerItem>
#include <QVBoxLayout>

using namespace AutomataLab;

InspectorLayout::InspectorLayout(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *boxLayout = new QVBoxLayout(this);
  stateName = new QLabel("Nothing!", this);
  stateName->setAccessibleName("label");
  boxLayout->addWidget(stateName);

  initialCheckbox = new QCheckBox("Is initial?", this);
  initialCheckbox->setAccessibleName("initialCheckbox");
  boxLayout->addWidget(initialCheckbox);
  connect(initialCheckbox, SIGNAL(stateChanged(int)), this,
          SLOT(initialCheckboxStateChanged(int)));

  finalCheckbox = new QCheckBox("Is final?", this);
  finalCheckbox->setAccessibleName("finalCheckbox");
  boxLayout->addWidget(finalCheckbox);
  connect(finalCheckbox, SIGNAL(stateChanged(int)), this,
          SLOT(finalCheckboxStateChanged(int)));

  boxLayout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
  QSpacerItem *spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding);
  boxLayout->addItem(spacer);

  this->setLayout(boxLayout);

  invalidate();
}

void InspectorLayout::setState(StateDrawable *state) {
  _state = state;
  invalidate();
}

StateDrawable *InspectorLayout::state() { return _state; }

int InspectorLayout::index() { return _index; }

void InspectorLayout::focus() { box->setCurrentIndex(index()); }

void InspectorLayout::attach(QToolBox *box) {
  int count = box->count();
  box->addItem(this, "Inspector layout");
  _index = count;
  this->box = box;
}

bool InspectorLayout::isAttached() { return box != nullptr; }

void InspectorLayout::invalidate() {
  if (state() == nullptr) {
    stateName->setText("Nothing!");
    initialCheckbox->setEnabled(false);
    finalCheckbox->setEnabled(false);
  } else {
    stateName->setText(tr("State : ") + state()->label());
    initialCheckbox->setEnabled(true);
    finalCheckbox->setEnabled(true);
    initialCheckbox->setChecked(state()->isInitial());
    finalCheckbox->setChecked(state()->isFinal());
  }
}

void InspectorLayout::initialCheckboxStateChanged(int currentState) {
  if (currentState == Qt::Checked) {
    emit stateSetInitial(state());
  } else {
    state()->setInitial(false);
  }
}

void InspectorLayout::finalCheckboxStateChanged(int currentState) {
  state()->setFinal(currentState == Qt::Checked);
  state()->update();
}

void InspectorLayout::detach() {
  box->removeItem(index());
  box->repaint();
  box = nullptr;
}
