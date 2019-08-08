#include <QtGui>
#include "mainwindow.h"
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QFont>
#include <QString>
#include "qledindicator.h"

#include <iostream>
#include <sstream>
#include <cmath>


MainWindow::MainWindow(QWidget *parent) :
  QWidget(parent) {
  setFixedSize(400,400);

  freq_entry = new QSpinBox(this);
  freq_entry->setMaximum(40000000);
  freq_entry->setGeometry(10, 10, 120, 30);

  freq_entry_label = new QLabel("Hz", this);
  freq_entry_label->setGeometry(140, 10, 20, 30);

  start_button = new QPushButton("Start", this);
  start_button->setGeometry(170,10,60,30);
  start_button->setCheckable(true);


  time_entry = new QSpinBox(this);
  time_entry->setMaximum(pow(2,32));
  time_entry->setGeometry(10, 50, 120, 30);

  time_entry_label = new QLabel("ms", this);
  time_entry_label->setGeometry(140, 50, 20, 30);

  run_for_button = new QPushButton("Run for", this);
  run_for_button->setGeometry(170,50,60,30);

  status_label = new QLabel("", this);
  status_label->setGeometry(10, 120, 250, 30);
  QFont status_font = status_label->font();
  status_font.setPointSize(11);
  status_font.setBold(true);
  status_label->setFont(status_font);

  status_led = new QLedIndicator(this);
  status_led->setGeometry(180, 120, 30, 30);
  status_led->setEnabled(false);


  /* Signals */
  connect(run_for_button, SIGNAL(pressed()), this, SLOT(handle_run_for()));
  connect(start_button, SIGNAL(clicked(bool)), this, SLOT(handle_start(bool)));
  connect(freq_entry, SIGNAL(valueChanged(int)), this, SLOT(freq_changed(int)));
  connect(time_entry, SIGNAL(valueChanged(int)), this, SLOT(run_time_changed(int)));

}

void MainWindow::handle_run_for(){
  start_button->setChecked(0);
  status_led->setChecked(true);

  std::stringstream ss;
  ss << "Freq: " << freq << " Hz\n" << "Time: " << run_time_ms << "ms";
  QString QStr = QString::fromStdString(ss.str());
  status_label->setText(QStr);

  status_led->setChecked(false);
}

void MainWindow::handle_start(bool checked){
  if(checked){
    std::stringstream ss;
    ss << "Freq: " << freq << " Hz";
    QString QStr = QString::fromStdString(ss.str());
    status_label->setText(QStr);
    status_led->setChecked(true);
  }
  else{
    status_led->setChecked(false);
  }
}

void MainWindow::freq_changed(int val){
  freq = val;
}

void MainWindow::run_time_changed(int val){
  run_time_ms = val;
}
