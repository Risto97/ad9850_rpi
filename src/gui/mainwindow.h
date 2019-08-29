#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QTabWidget>
#include <QWidget>
#include <QMenu>
#include <QApplication>

#include "qledindicator.h"
#include "config_dialog.hpp"
#include "status_box.h"
#include "basic_tab.h"
#include "sweep_tab.h"
#include "ad9850.hpp"
#include "ad9850_threads.h"
#include "config.hpp"

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

  ConfigDialog *config_dialog;

  RunForThr *run_for_thrd;
  RunThr *run_thrd;
  SweepThr *sweep_thrd;

  AD9850 *ad9850;
  Cfg *cfg;

signals:
  void finish();
  void stop();

public slots:
  void handle_run(unsigned int f_val);
  void handle_run_for(unsigned int f_val, unsigned int time_ms);
  void handle_sweep(unsigned int start_f, unsigned int stop_f, unsigned int step_f, unsigned int step_t_ms);
  void handle_stop();
  void handle_finish();

  void handle_pop_config();
  void handle_read_config();
};

#endif // MAINWINDOW_H
