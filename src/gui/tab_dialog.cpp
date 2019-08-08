#include "tab_dialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

#include <cmath>
#include <iostream>

MainTab::MainTab(QWidget *parent) : QWidget(parent) {

  freq_entry = new QSpinBox(this);
  freq_entry->setMaximum(40000000);
  freq_entry->setGroupSeparatorShown(true);

  freq_entry_label = new QLabel("Hz", this);

  run_button = new QPushButton("Start", this);
  run_button->setCheckable(true);

  time_entry = new QSpinBox(this);
  time_entry->setMaximum(pow(2, 31));
  time_entry->setGroupSeparatorShown(true);

  time_entry_label = new QLabel("ms", this);

  run_for_button = new QPushButton("Run for", this);

  QGridLayout *mainLayout = new QGridLayout();
  mainLayout->addWidget(freq_entry, 0, 0);
  mainLayout->addWidget(freq_entry_label, 0, 1);
  mainLayout->addWidget(run_button, 0, 2);

  mainLayout->addWidget(time_entry, 1, 0);
  mainLayout->addWidget(time_entry_label, 1, 1);
  mainLayout->addWidget(run_for_button, 1, 2);

  setLayout(mainLayout);

  /* Signals and slots */

  connect(freq_entry, SIGNAL(valueChanged(int)), this,
          SLOT(handle_freq_changed(int)));
  connect(time_entry, SIGNAL(valueChanged(int)), this,
          SLOT(handle_time_changed(int)));
  connect(run_for_button, SIGNAL(pressed()), this, SLOT(handle_run_for()));
  connect(run_button, SIGNAL(clicked(bool)), this, SLOT(handle_run(bool)));
}

void MainTab::handle_freq_changed(int val) { freq = val; }

void MainTab::handle_time_changed(int val) { run_time_ms = val; }

void MainTab::handle_run_for() {
  run_button->setChecked(0);
  emit run_for(freq, run_time_ms);
}

void MainTab::handle_run(bool checked) {
  if (checked) {
    emit run(freq);
  } else {
    emit stop();
  }
}

void MainTab::handle_stop() { run_button->setChecked(0); }
