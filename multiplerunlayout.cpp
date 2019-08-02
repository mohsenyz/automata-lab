#include "multiplerunlayout.h"
#include <QBoxLayout>
#include <QVBoxLayout>

using namespace AutomataLab;

MultipleRunLayout::MultipleRunLayout(QWidget *parent, Machine *machine)
    : QWidget(parent) {
  setMachine(machine);
  QVBoxLayout *boxLayout = new QVBoxLayout(this);
  tableWidget = new QTableWidget();
  tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  tableWidget->verticalHeader()->setVisible(false);
  tableWidget->setColumnCount(2);
  tableWidget->setHorizontalHeaderLabels({"Input", "Output"});

  for (int row = 0; row < 25; row++) {
    QTableWidgetItem *item0 = new QTableWidgetItem("");
    QTableWidgetItem *item1 = new QTableWidgetItem("");
    item1->setTextColor(Qt::white);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setFlags(Qt::ItemIsSelectable);
    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setItem(row, 0, item0);
    tableWidget->setItem(row, 1, item1);
  }
  for (int c = 0; c < tableWidget->horizontalHeader()->count(); ++c) {
    tableWidget->horizontalHeader()->setSectionResizeMode(c,
                                                          QHeaderView::Stretch);
  }
  boxLayout->addWidget(tableWidget);

  boxLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
  QSpacerItem *spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding);
  boxLayout->addItem(spacer);

  QPushButton *addRow = new QPushButton("Add row");
  removeSelectedBtn = new QPushButton("Remove selected");
  removeSelectedBtn->setEnabled(false);
  QHBoxLayout *controlLayout = new QHBoxLayout();
  controlLayout->addWidget(addRow);
  controlLayout->addWidget(removeSelectedBtn);

  boxLayout->addLayout(controlLayout);

  QPushButton *runBtn = new QPushButton("Run all");
  boxLayout->addWidget(runBtn);

  connect(addRow, SIGNAL(clicked()), this, SLOT(on_addRowBtn_clicked()));
  connect(removeSelectedBtn, SIGNAL(clicked()), this,
          SLOT(on_removeSelectedBtn_clicked()));
  connect(runBtn, SIGNAL(clicked()), this, SLOT(on_runBtn_clicked()));
  connect(tableWidget, SIGNAL(cellDoubleClicked(int, int)), this,
          SLOT(on_tableCell_changed(int, int)));
  connect(tableWidget, SIGNAL(itemSelectionChanged()), this,
          SLOT(on_tableSelection_changed()));

  this->setLayout(boxLayout);
}

void MultipleRunLayout::setMachine(Machine *machine) { _machine = machine; }

int MultipleRunLayout::index() { return _index; }

void MultipleRunLayout::focus() { box->setCurrentIndex(index()); }

void MultipleRunLayout::attach(QToolBox *box) {
  int count = box->count();
  box->addItem(this, "Multiple run");
  _index = count;
  this->box = box;
}

void MultipleRunLayout::on_runBtn_clicked() {
  for (int i = 0; i < tableWidget->rowCount(); i++) {
    QTableWidgetItem *item = tableWidget->item(i, 0);
    QTableWidgetItem *resultItem = tableWidget->item(i, 1);
    if (!item->text().trimmed().isEmpty()) {
      _machine->prepareRun();
      Tape *tape = new Tape(item->text().trimmed());
      _machine->setTape(tape);

      if (_machine->run()) {
        resultItem->setText("Accepted");
        resultItem->setBackgroundColor(QColor(129, 199, 132));
      } else {
        resultItem->setText("Rejected");
        resultItem->setBackgroundColor(QColor(229, 115, 115));
      }
      if (_machine->type() == TURING) {
        resultItem->setText(tape->toString());
      }
      delete tape;
    }
  }
  tableWidget->clearSelection();
}

void MultipleRunLayout::on_addRowBtn_clicked() {
  QTableWidgetItem *item0 = new QTableWidgetItem("");
  QTableWidgetItem *item1 = new QTableWidgetItem("");
  item1->setTextColor(Qt::white);
  item1->setTextAlignment(Qt::AlignCenter);
  item1->setFlags(Qt::ItemIsSelectable);
  int row = tableWidget->rowCount();
  tableWidget->insertRow(row);
  tableWidget->setItem(row, 1, item1);
  tableWidget->setItem(row, 0, item0);
}

void MultipleRunLayout::on_removeSelectedBtn_clicked() {
  for (auto item : tableWidget->selectedItems()) {
    tableWidget->removeRow(item->row());
  }
}

void MultipleRunLayout::on_tableSelection_changed() {
  if (tableWidget->selectedItems().size() > 0) {
    removeSelectedBtn->setEnabled(true);
  } else {
    removeSelectedBtn->setEnabled(false);
  }
}

void MultipleRunLayout::on_tableCell_changed(int row, int column) {
  auto item = tableWidget->item(row, 1);
  item->setBackgroundColor(Qt::white);
  item->setText("");
}

bool MultipleRunLayout::isAttached() { return box != nullptr; }
