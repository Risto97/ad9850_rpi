#include "mainwindow.h"

#include <cmath>
#include <iostream>
#include <sstream>

MainWindow::MainWindow() {
  // setFixedSize(800, 400);

  ad9850_init();
  ad9850_rst();

  StatusBox *status_box = new StatusBox(this);
  setCentralWidget(status_box);

  basic_tab = new BasicTab();
  sweep_tab = new SweepTab();

  tabWidget = new QTabWidget;
  tabWidget->addTab(basic_tab, tr("Basic"));
  tabWidget->addTab(sweep_tab, tr("Sweep"));

  main_layout = new QHBoxLayout;
  main_layout->addWidget(tabWidget);
  main_layout->addWidget(status_box);

  window = new QWidget();
  window->setLayout(main_layout);
  setCentralWidget(window);

  // /* Signals */
  connect(basic_tab, SIGNAL(run(unsigned int)), this,
          SLOT(handle_run(unsigned int)));
  connect(basic_tab, SIGNAL(run_for(unsigned int, unsigned int)), this,
          SLOT(handle_run_for(unsigned int, unsigned int)));
  connect(basic_tab, SIGNAL(stop()), this, SLOT(handle_stop()));

  connect(basic_tab, SIGNAL(run(unsigned int)), status_box,
          SLOT(handle_run(unsigned int)));
  connect(basic_tab, SIGNAL(run_for(unsigned int, unsigned int)), status_box,
          SLOT(handle_run_for(unsigned int, unsigned int)));

  connect(sweep_tab, SIGNAL(stop()), this, SLOT(handle_stop()));
  connect(sweep_tab, SIGNAL(sweep(unsigned int, unsigned int, unsigned int, unsigned int)), this, SLOT(handle_sweep(unsigned int, unsigned int, unsigned int, unsigned int)));
  connect(sweep_tab, SIGNAL(sweep(unsigned int, unsigned int, unsigned int, unsigned int)), status_box, SLOT(handle_sweep(unsigned int, unsigned int, unsigned int, unsigned int)));

  connect(status_box, SIGNAL(stop()), this, SLOT(handle_stop()));
  connect(this, SIGNAL(stop()), basic_tab, SLOT(handle_stop()));
  connect(this, SIGNAL(stop()), status_box, SLOT(handle_stop()));
  connect(this, SIGNAL(stop()), sweep_tab, SLOT(handle_stop()));
  // connect(this, SIGNAL(finish()), status_box, SLOT(handle_stop()));
  connect(this, SIGNAL(finish()), this, SLOT(handle_finish()));


  /* THREADS */

  run_for_thrd = new RunForThr();
  run_thrd = new RunThr();
  sweep_thrd = new SweepThr();

  connect(run_for_thrd, SIGNAL(finished()), this, SLOT(handle_finish()));

}

void MainWindow::handle_run(unsigned int f_val) {
  run_thrd->start_with(f_val);
}

void MainWindow::handle_run_for(unsigned int f_val, unsigned int time_ms) {
  run_for_thrd->start_with(f_val, time_ms);
}

void MainWindow::handle_sweep(unsigned int start_f, unsigned int stop_f, unsigned int step_f, unsigned int step_t_ms)
{
  sweep_thrd->start_with(start_f, stop_f, step_f, step_t_ms);
}

void MainWindow::handle_stop() {
  run_for_thrd->stop();
  run_thrd->stop();
  sweep_thrd->stop();
  emit stop();
}
void MainWindow::handle_finish() {
  emit stop();
}
