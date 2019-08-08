#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include "qledindicator.h"

class MainWindow : public QWidget
{
  Q_OBJECT
 public:
  explicit MainWindow(QWidget *parent = 0);

 private:
  QPushButton *start_button;
  QSpinBox *freq_entry;
  QLabel *freq_entry_label;

  QSpinBox *time_entry;
  QPushButton *run_for_button;
  QLabel *time_entry_label;

  QLabel *status_label;
  QLedIndicator *status_led;

  unsigned int freq = 0;
  unsigned int run_time_ms = 0;

 signals:
  public slots:
   void handle_run_for();
   void handle_start(bool checked);
   void freq_changed(int val);
   void run_time_changed(int val);

};

#endif // MAINWINDOW_H
