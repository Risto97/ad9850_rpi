#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "qledindicator.h"
#include "status_box.h"
#include "tab_dialog.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow();

private:
  QWidget *window;
  QHBoxLayout *main_layout;
  StatusBox *status_box;

  QTabWidget *tabWidget;
  MainTab *main_tab;

signals:
  void finish();
  void stop();

public slots:
  void handle_run(unsigned int f_val);
  void handle_run_for(unsigned int f_val, unsigned int time_ms);
  void handle_stop();
};

#endif // MAINWINDOW_H
