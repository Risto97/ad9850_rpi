#ifndef CONFIG_DIALOG_HPP_
#define CONFIG_DIALOG_HPP_

#include <QWidget>
#include <QDialog>
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <Qt>
#include <QtGui>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include "config.hpp"
#include <QComboBox>
#include <vector>
#include <QLabel>
#include <QStringList>
#include <iostream>
#include <QSpinBox>

class ConfigDialog: public QDialog
{
  Q_OBJECT
public:
  explicit ConfigDialog(QWidget *p = 0): QDialog(p) {

    for(int i = 1; i < 17; i++){
      wiringPi_pn_qstr << QString::number(i);
      wiringPi_pn.push_back(i);
    }
    for(int i = 22; i < 31; i++){
      wiringPi_pn_qstr << QString::number(i);
      wiringPi_pn.push_back(i);
    }

    cfg = new Cfg();
    int ret = cfg->read();

    QGridLayout *layout = new QGridLayout();

    // QVBoxLayout *layout = new QVBoxLayout(this);
    w_clk_l = new QComboBox(this);
    QLabel *w_clk_label = new QLabel("W_CLK pin");
    w_clk_l->addItems(wiringPi_pn_qstr);
    w_clk_l->setCurrentIndex(find_combo_index(cfg->w_clk, w_clk_l));

    fq_ud_l = new QComboBox(this);
    QLabel *fq_ud_label = new QLabel("FQ_UD pin");
    fq_ud_l->addItems(wiringPi_pn_qstr);
    fq_ud_l->setCurrentIndex(find_combo_index(cfg->fq_ud, fq_ud_l));

    data_l = new QComboBox(this);
    QLabel *data_label = new QLabel("DATA pin");
    data_l->addItems(wiringPi_pn_qstr);
    data_l->setCurrentIndex(find_combo_index(cfg->data, data_l));

    rst_l = new QComboBox(this);
    QLabel *rst_label = new QLabel("RST pin");
    rst_l->addItems(wiringPi_pn_qstr);
    rst_l->setCurrentIndex(find_combo_index(cfg->rst, rst_l));

    QSpinBox *dds_clk_entry = new QSpinBox(this);
    QLabel *dds_clk_label = new QLabel("DDS CLK freq");
    dds_clk_entry->setGroupSeparatorShown(true);
    dds_clk_entry->setMaximum(1000000000);
    dds_clk_entry->setGroupSeparatorShown(true);
    dds_clk_entry->setSuffix(" Hz");
    dds_clk_entry->setValue(cfg->dds_clk);

    QPushButton *ok_button = new QPushButton("Ok", this);
    QPushButton *save_button = new QPushButton("Save config", this);

    layout->addWidget(w_clk_l, 0, 0);
    layout->addWidget(w_clk_label, 0, 1);

    layout->addWidget(fq_ud_l, 1, 0);
    layout->addWidget(fq_ud_label, 1, 1);

    layout->addWidget(data_l, 2, 0);
    layout->addWidget(data_label, 2, 1);

    layout->addWidget(rst_l, 3, 0);
    layout->addWidget(rst_label, 3, 1);

    layout->addWidget(dds_clk_entry, 4, 0);
    layout->addWidget(dds_clk_label, 4, 1);

    layout->addWidget(ok_button, 5,0);
    layout->addWidget(save_button, 5,1);
    setLayout(layout);

    connect(ok_button, SIGNAL(clicked()), SLOT(accept()));
    connect(save_button, SIGNAL(clicked()), this, SLOT(handle_save_cfg()));

    connect(w_clk_l, SIGNAL(currentTextChanged(QString)), this, SLOT(handle_w_clk_change(QString)));
    connect(fq_ud_l, SIGNAL(currentTextChanged(QString)), this, SLOT(handle_fq_ud_change(QString)));
    connect(data_l, SIGNAL(currentTextChanged(QString)), this, SLOT(handle_data_change(QString)));
    connect(rst_l, SIGNAL(currentTextChanged(QString)), this, SLOT(handle_rst_change(QString)));
    connect(dds_clk_entry, SIGNAL(valueChanged(int)), this, SLOT(handle_dds_clk_change(int)));
  }

  int find_combo_index(int val, QComboBox *box){
    int index = box->findText(QString::number(val));
    if( index != -1){
      return index;
    }
  }

public slots:
  void handle_save_cfg(){
    cfg->write();
  }

  void handle_w_clk_change(QString text){
    cfg->w_clk = text.toInt();
  }

  void handle_fq_ud_change(QString text){
    cfg->fq_ud = text.toInt();
  }

  void handle_data_change(QString text){
    cfg->data = text.toInt();
  }

  void handle_rst_change(QString text){
    cfg->rst = text.toInt();
  }

  void handle_dds_clk_change(int val){
    cfg->dds_clk = val;
  }

private:
  QComboBox *w_clk_l;
  QComboBox *fq_ud_l;
  QComboBox *data_l;
  QComboBox *rst_l;
  QComboBox *dds_clk_l;

  std::vector<unsigned int> wiringPi_pn;
  QStringList wiringPi_pn_qstr;

  Cfg *cfg;
};

#endif
