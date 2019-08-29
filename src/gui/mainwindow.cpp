#include "mainwindow.h"

#include <cmath>
#include <iostream>
#include <sstream>

#include <QMenuBar>
#include <QInputDialog>
#include <QString>
#include <QLineEdit>

MainWindow::MainWindow() {
  // setFixedSize(800, 400);
  cfg = new Cfg();
  int asd = cfg->read();

  ad9850 = new AD9850(cfg);

  ad9850->init();
  ad9850->rst();

  QAction *show_config = new QAction("&config", this);

  QMenu *config_menu;
  config_menu = menuBar()->addMenu("&config");
  config_menu->addAction(show_config);

  config_dialog = new ConfigDialog();

  connect(show_config, SIGNAL(triggered()), this, SLOT(handle_pop_config()));


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

  connect(config_dialog, SIGNAL(accepted()), this, SLOT(handle_read_config()));

  connect(status_box, SIGNAL(stop()), this, SLOT(handle_stop()));
  connect(this, SIGNAL(stop()), basic_tab, SLOT(handle_stop()));
  connect(this, SIGNAL(stop()), status_box, SLOT(handle_stop()));
  connect(this, SIGNAL(stop()), sweep_tab, SLOT(handle_stop()));
  // connect(this, SIGNAL(finish()), status_box, SLOT(handle_stop()));
  connect(this, SIGNAL(finish()), this, SLOT(handle_finish()));


  /* THREADS */

  run_thrd = new RunThr(ad9850);
  run_for_thrd = new RunForThr(ad9850);
  sweep_thrd = new SweepThr(ad9850);

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

void MainWindow::handle_pop_config() {
  config_dialog->open();
}

void MainWindow::handle_read_config(){
  cfg->read();
  ad9850->set_vals(cfg);
}
