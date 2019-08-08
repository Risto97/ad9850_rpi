#ifndef _STATUS_BOX_H
#define _STATUS_BOX_H

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

#include "qledindicator.h"

class StatusBox : public QWidget {
  Q_OBJECT

private:
  QGroupBox *box;
  QLabel *status_label;
  QLedIndicator *status_led;
  QPushButton *stop_button;

signals:
  void stop();

public slots:
  void handle_run(unsigned int f_val);
  void handle_stop();
  void handle_run_for(unsigned int f_val, unsigned int time_ms);
  void handle_stop_button();

public:
  explicit StatusBox(QWidget *parent = 0);
};

#endif
