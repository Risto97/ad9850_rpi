#ifndef _STATUS_BOX_H
#define _STATUS_BOX_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include "qledindicator.h"

class StatusBox : public QWidget {
  Q_OBJECT

private:
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
  void handle_sweep(unsigned int start_f, unsigned int stop_f, unsigned int step_f, unsigned int step_t_ms);

public:
  explicit StatusBox(QWidget *parent = 0);
};

#endif
