#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGui>

#include "mainwindow.h"
#include "qledindicator.h"
#include "status_box.h"
#include "tab_dialog.h"

#include <cmath>
#include <iostream>
#include <sstream>

MainWindow::MainWindow() {
  // setFixedSize(800, 400);

  StatusBox *status_box = new StatusBox(this);
  setCentralWidget(status_box);

  main_tab = new MainTab();

  tabWidget = new QTabWidget;
  tabWidget->addTab(main_tab, tr("General"));
  // tabWidget->addTab(new MainTab(), tr("ASDDD"));

  main_layout = new QHBoxLayout;
  main_layout->addWidget(tabWidget);
  main_layout->addWidget(status_box);

  window = new QWidget();
  window->setLayout(main_layout);
  setCentralWidget(window);

  // /* Signals */
  connect(main_tab, SIGNAL(run(unsigned int)), this,
          SLOT(handle_run(unsigned int)));
  connect(main_tab, SIGNAL(run(unsigned int)), status_box,
          SLOT(handle_run(unsigned int)));
  connect(main_tab, SIGNAL(run_for(unsigned int, unsigned int)), status_box,
          SLOT(handle_run_for(unsigned int, unsigned int)));
  connect(main_tab, SIGNAL(stop()), status_box, SLOT(handle_stop()));
  connect(this, SIGNAL(finish()), status_box, SLOT(handle_stop()));
  connect(status_box, SIGNAL(stop()), this, SLOT(handle_stop()));
  connect(this, SIGNAL(stop()), main_tab, SLOT(handle_stop()));
}

void MainWindow::handle_run(unsigned int f_val) {}

void MainWindow::handle_run_for(unsigned int f_val, unsigned int time_ms) {}

void MainWindow::handle_stop() { emit stop(); }
