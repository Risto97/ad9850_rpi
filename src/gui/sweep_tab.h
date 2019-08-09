#ifndef _SWEEP_TAB_H
#define _SWEEP_TAB_H

#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

class SweepTab : public QWidget {
  Q_OBJECT

 private:
  QSpinBox *start_entry;
  QSpinBox *stop_entry;
  QSpinBox *step_entry;
  QSpinBox *time_entry;

  QPushButton *sweep_button;

  QLabel *start_entry_label;
  QLabel *stop_entry_label;
  QLabel *step_entry_label;
  QLabel *time_entry_label;

  unsigned int start_freq = 0;
  unsigned int stop_freq = 0;
  unsigned int step_freq = 0;
  unsigned int step_time_ms = 0;

 signals:
  void sweep(unsigned int start_f, unsigned int stop_f, unsigned int step_f, unsigned int step_t_ms);
  void stop();

  public slots:
    void handle_start_freq_changed(int val);
    void handle_stop_freq_changed(int val);
    void handle_step_freq_changed(int val);
    void handle_step_time_changed(int val);
    void handle_sweep();
    void handle_stop();

 public:
    explicit SweepTab(QWidget *parent = 0);
};

#endif
