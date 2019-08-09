#include "sweep_tab.h"
#include <QGridLayout>
#include <QVBoxLayout>

#include <cmath>
#include <iostream>

SweepTab::SweepTab(QWidget *parent) : QWidget(parent) {

  QVBoxLayout *start_box = new QVBoxLayout();
  start_entry_label = new QLabel("Start frequency");
  start_entry = new QSpinBox(this);
  start_entry->setMaximum(40000000);
  start_entry->setGroupSeparatorShown(true);
  start_entry->setSuffix(" Hz");

  start_box->addWidget(start_entry_label);
  start_box->addWidget(start_entry);
  start_box->addStretch();

  QVBoxLayout *stop_box = new QVBoxLayout();
  stop_entry_label = new QLabel("Stop frequency");
  stop_entry = new QSpinBox(this);
  stop_entry->setMaximum(40000000);
  stop_entry->setGroupSeparatorShown(true);
  stop_entry->setSuffix(" Hz");

  stop_box->addWidget(stop_entry_label);
  stop_box->addWidget(stop_entry);
  stop_box->addStretch();

  QVBoxLayout *step_box = new QVBoxLayout();
  step_entry_label = new QLabel("Step frequency");
  step_entry = new QSpinBox(this);
  step_entry->setMaximum(40000000);
  step_entry->setGroupSeparatorShown(true);
  step_entry->setSuffix(" Hz");

  step_box->addWidget(step_entry_label);
  step_box->addWidget(step_entry);
  step_box->addStretch();

  QVBoxLayout *time_box = new QVBoxLayout();
  time_entry_label = new QLabel("Step time in ms");
  time_entry = new QSpinBox(this);
  time_entry->setMaximum(40000000);
  time_entry->setGroupSeparatorShown(true);
  time_entry->setSuffix(" ms");

  time_box->addWidget(time_entry_label);
  time_box->addWidget(time_entry);
  time_box->addStretch();

  sweep_button = new QPushButton("Sweep", this);

  QGridLayout *mainLayout = new QGridLayout();
  mainLayout->addLayout(start_box, 0, 0);
  mainLayout->addLayout(stop_box, 0, 1);
  mainLayout->addLayout(step_box, 1, 0);
  mainLayout->addLayout(time_box, 1, 1);

  mainLayout->addWidget(sweep_button, 2, 1);

  setLayout(mainLayout);

  /* Signals and slots */

  connect(start_entry, SIGNAL(valueChanged(int)), this, SLOT(handle_start_freq_changed(int)));
  connect(stop_entry, SIGNAL(valueChanged(int)), this, SLOT(handle_stop_freq_changed(int)));
  connect(step_entry, SIGNAL(valueChanged(int)), this, SLOT(handle_step_freq_changed(int)));
  connect(time_entry, SIGNAL(valueChanged(int)), this, SLOT(handle_step_time_changed(int)));
  connect(sweep_button, SIGNAL(pressed()), this, SLOT(handle_sweep()));
}

void SweepTab::handle_start_freq_changed(int val) { start_freq = val; }
void SweepTab::handle_stop_freq_changed(int val) { stop_freq = val; }
void SweepTab::handle_step_freq_changed(int val) { step_freq = val; }
void SweepTab::handle_step_time_changed(int val) { step_time_ms = val; }

void SweepTab::handle_sweep() {
    emit stop();
    emit sweep(start_freq, stop_freq, step_freq, step_time_ms);
}

void SweepTab::handle_stop() {}
