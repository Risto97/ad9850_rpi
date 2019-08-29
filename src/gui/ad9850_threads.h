#ifndef _AD9850_THREADS
#define _AD9850_THREADS

#include <QThread>

#include <iostream>
#include <unistd.h>

#include "ad9850.hpp"

class RunThr : public QThread {
  Q_OBJECT

 private:
  bool keep_running;
  unsigned int freq;
  AD9850 *ad9850;

 public:

  RunThr(AD9850 *ad) : ad9850(ad){

  }

  void start_with(unsigned int f_val){
    freq = f_val;
    start();
  }

  public slots:
    void stop() {
      keep_running = false;
    }

 protected:
    void run() {
      keep_running = true;
      ad9850->run(freq);
    }
};

class RunForThr : public QThread {
  Q_OBJECT

private:
  bool keep_running;
  unsigned int freq;
  unsigned int time_ms;
  AD9850 *ad9850;

 public:

  RunForThr(AD9850 *ad) : ad9850(ad){}

  void start_with(unsigned int f_val, unsigned int t_val){
    freq = f_val;
    time_ms = t_val;
    start();
  }

public slots:
  void stop() {
    keep_running = false;
  }

protected:
  void run() {
    keep_running = true;
    ad9850->run_for(freq, time_ms, &keep_running);

  }
};

class SweepThr : public QThread {
  Q_OBJECT

 private:
  bool keep_running;
  unsigned int start_freq;
  unsigned int stop_freq;
  unsigned int step_freq;
  unsigned int step_time_ms;
  AD9850 *ad9850;

 public:


  SweepThr(AD9850 *ad) : ad9850(ad){}

  void start_with(unsigned int start_f_val, unsigned int stop_f_val, unsigned int step_f_val, unsigned int step_t_val){
    start_freq = start_f_val;
    stop_freq = stop_f_val;
    step_freq = step_f_val;
    step_time_ms = step_t_val;
    start();
  }

  public slots:
    void stop() {
      keep_running = false;
    }

 protected:
    void run() {
      keep_running = true;
      ad9850->sweep(start_freq, stop_freq, step_freq, step_time_ms, &keep_running);
    }
};

#endif
