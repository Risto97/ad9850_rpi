#include "basic_tab.h"
#include <QGridLayout>
#include <QVBoxLayout>

#include <cmath>
#include <iostream>

BasicTab::BasicTab(QWidget *parent) : QWidget(parent) {


  QVBoxLayout *freq_box = new QVBoxLayout();
  freq_entry = new QSpinBox(this);
  freq_entry->setMaximum(40000000);
  freq_entry->setGroupSeparatorShown(true);
  freq_entry->setSuffix(" Hz");
  freq_entry_label = new QLabel("Frequency.", this);

  freq_box->addWidget(freq_entry_label);
  freq_box->addWidget(freq_entry);
  freq_box->addStretch();

  run_button = new QPushButton("Start", this);

  QVBoxLayout *time_box = new QVBoxLayout();
  time_entry = new QSpinBox(this);
  time_entry->setMaximum(pow(2, 31));
  time_entry->setGroupSeparatorShown(true);
  time_entry->setSuffix(" ms");
  time_entry_label = new QLabel("Run time. (optional)", this);

  time_box->addWidget(time_entry_label);
  time_box->addWidget(time_entry);
  time_box->addStretch();

  run_for_button = new QPushButton("Run for", this);

  QGridLayout *mainLayout = new QGridLayout();
  mainLayout->addWidget(run_button, 1, 0);
  mainLayout->addWidget(run_for_button, 1, 1);
  mainLayout->addLayout(freq_box, 0,0);
  mainLayout->addLayout(time_box, 0,1);

  setLayout(mainLayout);

  /* Signals and slots */

  connect(freq_entry, SIGNAL(valueChanged(int)), this,
          SLOT(handle_freq_changed(int)));
  connect(time_entry, SIGNAL(valueChanged(int)), this,
          SLOT(handle_time_changed(int)));
  connect(run_for_button, SIGNAL(pressed()), this, SLOT(handle_run_for()));
  connect(run_button, SIGNAL(pressed()), this, SLOT(handle_run()));
}

void BasicTab::handle_freq_changed(int val) { freq = val; }

void BasicTab::handle_time_changed(int val) { run_time_ms = val; }

void BasicTab::handle_run_for() {
  emit stop();
  emit run_for(freq, run_time_ms);
}

void BasicTab::handle_run() {
  emit stop();
  emit run(freq);
}

void BasicTab::handle_stop() { }
