#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QTabWidget>
#include <QWidget>

#include "qledindicator.h"
#include "status_box.h"
#include "basic_tab.h"
#include "sweep_tab.h"
#include "ad9850.hpp"
#include "ad9850_threads.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow();

private:
  QWidget *window;
  QHBoxLayout *main_layout;
  StatusBox *status_box;

  QTabWidget *tabWidget;
  BasicTab *basic_tab;
  SweepTab *sweep_tab;

  RunForThr *run_for_thrd;
  RunThr *run_thrd;
  SweepThr *sweep_thrd;

signals:
  void finish();
  void stop();

public slots:
  void handle_run(unsigned int f_val);
  void handle_run_for(unsigned int f_val, unsigned int time_ms);
  void handle_sweep(unsigned int start_f, unsigned int stop_f, unsigned int step_f, unsigned int step_t_ms);
  void handle_stop();
  void handle_finish();
};

#endif // MAINWINDOW_H
