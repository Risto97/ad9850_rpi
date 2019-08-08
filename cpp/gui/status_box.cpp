#include <QFont>
#include <QGroupBox>
#include <QString>
#include <QWidget>

#include <iostream>
#include <sstream>

#include "qledindicator.h"
#include "status_box.h"

StatusBox::StatusBox(QWidget *parent) : QWidget(parent) {
  box = new QGroupBox(tr("Status box"));

  QVBoxLayout *status_layout = new QVBoxLayout();
  status_label = new QLabel("", this);
  QFont status_font = status_label->font();
  status_font.setPointSize(11);
  status_font.setBold(true);
  status_label->setFont(status_font);

  status_led = new QLedIndicator(this);
  // status_led->setGeometry(180, 120, 30, 30);
  status_led->setEnabled(false);

  stop_button = new QPushButton("Stop", this);

  status_layout->addWidget(status_label);
  status_layout->addWidget(status_led);
  status_layout->addWidget(stop_button);
  setLayout(status_layout);

  connect(stop_button, SIGNAL(pressed()), this, SLOT(handle_stop_button()));
}

void StatusBox::handle_run(unsigned int f_val) {
  status_led->setChecked(true);

  std::stringstream ss;
  ss << "Freq: " << f_val << " Hz\n";
  QString QStr = QString::fromStdString(ss.str());
  status_label->setText(QStr);
}

void StatusBox::handle_run_for(unsigned int f_val, unsigned int time_ms) {
  status_led->setChecked(true);

  std::stringstream ss;
  ss << "Freq: " << f_val << " Hz\n"
     << "For: " << time_ms << "ms";
  QString QStr = QString::fromStdString(ss.str());
  status_label->setText(QStr);

  status_led->setChecked(false);
}

void StatusBox::handle_stop() { status_led->setChecked(false); }

void StatusBox::handle_stop_button() {
  handle_stop();
  emit stop();
}
