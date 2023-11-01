#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QRegularExpressionValidator>
#include <iostream>

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 private:
  Ui::CreditWindow *ui;
  QRegularExpressionValidator input_validator;

 public slots:
  void on_pushButton_close_clicked();

 private slots:
  void on_pushButton_calculate_clicked();
  void calculate_credit();
};

#endif  // CREDITWINDOW_H
