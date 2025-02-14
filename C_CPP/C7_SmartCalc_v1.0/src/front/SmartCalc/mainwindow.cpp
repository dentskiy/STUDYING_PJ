#include "mainwindow.h"

#include <QByteArray>
#include <QLineEdit>
#include <QPainter>
#include <QString>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

// calc----------------------------------
void MainWindow::on_pushButton_clicked() {
  char res[256];
  QString text = ui->lineEdit->text();
  QByteArray c_text = text.toLatin1();
  char *str = c_text.data();
  double x[POINTC], y[POINTC];
  for (int i = 0; i < POINTC; i++) {
    x[i] = -5. + 0.1 * i;
  }
  if (*str) {
    int err = s21_SmartCalc(str, res, x, y, ui->doubleSpinBox->value());
    if (!err) {
      ui->statusbar->clearMessage();
      ui->widget->setFunc(y);
      ui->lineEdit->setText(res);
    } else {
      ui->statusbar->showMessage("Calc: Status: Error", 0);
    }
  } else {
    ui->lineEdit->setText("");
  }
}

void MainWindow::on_pushButton_4_clicked() { ui->lineEdit->insert("1"); }

void MainWindow::on_pushButton_3_clicked() { ui->lineEdit->insert("2"); }

void MainWindow::on_pushButton_2_clicked() { ui->lineEdit->insert("3"); }

void MainWindow::on_pushButton_5_clicked() { ui->lineEdit->insert("4"); }

void MainWindow::on_pushButton_6_clicked() { ui->lineEdit->insert("5"); }

void MainWindow::on_pushButton_9_clicked() { ui->lineEdit->insert("6"); }

void MainWindow::on_pushButton_7_clicked() { ui->lineEdit->insert("7"); }

void MainWindow::on_pushButton_8_clicked() { ui->lineEdit->insert("8"); }

void MainWindow::on_pushButton_10_clicked() { ui->lineEdit->insert("9"); }

void MainWindow::on_pushButton_12_clicked() { ui->lineEdit->insert("0"); }

void MainWindow::on_pushButton_13_clicked() { ui->lineEdit->insert("."); }

void MainWindow::on_pushButton_18_clicked() { ui->lineEdit->insert("("); }

void MainWindow::on_pushButton_19_clicked() { ui->lineEdit->insert(")"); }

void MainWindow::on_pushButton_20_clicked() { ui->lineEdit->backspace(); }

void MainWindow::on_pushButton_11_clicked() { ui->lineEdit->insert("/"); }

void MainWindow::on_pushButton_14_clicked() { ui->lineEdit->insert("*"); }

void MainWindow::on_pushButton_15_clicked() { ui->lineEdit->insert("-"); }

void MainWindow::on_pushButton_16_clicked() { ui->lineEdit->insert("+"); }

void MainWindow::on_pushButton_17_clicked() { ui->lineEdit->insert("mod"); }

void MainWindow::on_pushButton_26_clicked() { ui->lineEdit->insert("sqrt("); }

void MainWindow::on_pushButton_21_clicked() { ui->lineEdit->insert("cos("); }

void MainWindow::on_pushButton_22_clicked() { ui->lineEdit->insert("sin("); }

void MainWindow::on_pushButton_23_clicked() { ui->lineEdit->insert("tan("); }

void MainWindow::on_pushButton_24_clicked() { ui->lineEdit->insert("ln("); }

void MainWindow::on_pushButton_25_clicked() { ui->lineEdit->insert("acos("); }

void MainWindow::on_pushButton_27_clicked() { ui->lineEdit->insert("asin("); }

void MainWindow::on_pushButton_28_clicked() { ui->lineEdit->insert("atan("); }

void MainWindow::on_pushButton_29_clicked() { ui->lineEdit->insert("log("); }

void MainWindow::on_pushButton_30_clicked() { ui->lineEdit->insert("x"); }

void MainWindow::on_pushButton_31_clicked() { ui->lineEdit->insert("^("); }

void MainWindow::on_pushButton_32_clicked() { ui->lineEdit->insert("^(2)"); }
//-----------------------------------------

// credit-----------------------------------

void MainWindow::on_pushButton_33_clicked() {
  int credit = ui->spinBox->value();
  int procent = ui->spinBox_2->value();
  int month = ui->spinBox_3->value();
  int res = 0;
  if (ui->comboBox->currentIndex()) {
    res = s21_creditDif(credit, month, procent);
    ui->label_6->setText("");
    ui->label_7->setText(QString::number(credit));
    ui->label_9->setText(QString::number(res - credit));
    ui->label_11->setText(QString::number(res));
  } else {
    res = s21_creditA(credit, month, procent);
    ui->label_6->setText(QString::number(res));
    ui->label_7->setText(QString::number(credit));
    ui->label_9->setText(QString::number(res * month - credit));
    ui->label_11->setText(QString::number(res * month));
  }
}

//-----------------------------------------

void MainWindow::on_checkBox_stateChanged(int arg1) {
  if (arg1) {
    ui->label_31->setText("Периодичность капитализации");
    ui->comboBox_3->removeItem(0);
  } else {
    ui->label_31->setText("Периодичность выплат");
    ui->comboBox_3->insertItem(0, "В конце срока");
  }
  ui->comboBox_3->setCurrentIndex(0);
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index) {
  if (!index)
    ui->spinBox_5->setMaximum(0);
  else
    ui->spinBox_5->setMaximum(1000000);
}

void MainWindow::on_pushButton_34_clicked() {
  deposit *dep = new deposit;
  dep->sum = ui->spinBox_4->value();
  dep->pc = ui->spinBox_10->value();
  dep->pn = ui->spinBox_11->value();
  dep->month = ui->spinBox_9->value();
  dep->kflag = ui->checkBox->isChecked();
  dep->period = ui->comboBox_3->currentIndex();
  dep->perup = ui->comboBox_2->currentIndex();
  dep->sumup = ui->spinBox_5->value();
  dep->result = dep->sum;
  dep->tax = 0.;
  s21_deposit(dep);
  ui->label_20->setText(QString::number((int)(dep->result - dep->sum)));
  ui->label_21->setText(QString::number((int)dep->tax));
  ui->label_22->setText(QString::number((int)dep->result));
  delete dep;
}
