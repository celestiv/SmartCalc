#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QString>

#include "./ui_mainwindow.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "plot.h"

#define MAX_LEN 256
#define MAX_PRECISION 15
#define REGEX "^[(sin|cos|ln|tan|log|mod|asin|atan|acos|sqrt|)0-9^/*-+xe.]{255}"

extern "C" {
double s21_smart_calc(const char *str, double input_X);
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  CreditWindow *credit;
  DepositWindow *deposit;
  Plot *plot;
  int credit_flag;
  int deposit_flag;
  int plot_flag;

  QRegularExpressionValidator input_X_validator;
  int bracket_count;
  int dot_count;

 private slots:
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
  void on_pushButton_plot_clicked();

  void digits();
  void punctuations();
  void functions();
  int is_function(QPushButton *button);
  int conditions(Ui::MainWindow *ui);
  void calculate();
  void send_data();
};
#endif  // MAINWINDOW_H
