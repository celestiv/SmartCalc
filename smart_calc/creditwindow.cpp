#include "creditwindow.h"

#include "ui_creditwindow.h"

extern "C" {
double annuity_credit(double percent, double credit_sum, double months,
                      double* sum_to_pay, double* overpayment);
double differentiate_credit(double percent, double credit_sum, double months,
                            double* sum_to_pay, double* overpayment);
}

CreditWindow::CreditWindow(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::CreditWindow),
      input_validator(QRegularExpression("[0-9.]{25}")) {
  ui->setupUi(this);
  ui->radioButton_annuity->setChecked(true);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_pushButton_close_clicked() { close(); }

void CreditWindow::on_pushButton_calculate_clicked() {
  CreditWindow::calculate_credit();
}

void CreditWindow::calculate_credit() {
  double percent = ui->lineEdit_percent->text().toDouble();
  double credit_sum = ui->lineEdit_sum->text().toDouble();
  double months = 0.0;
  if (ui->comboBox->currentText() == "Месяцев") {
    months = ui->lineEdit_months->text().toDouble();
  } else if (ui->comboBox->currentText() == "Лет") {
    months = ui->lineEdit_months->text().toDouble() * 12;
  }
  if (months <= 0 || percent <= 0 || credit_sum <= 0 ||
      credit_sum >= __INT64_MAX__ || percent >= 100 || months >= 50 * 12 + 1) {
    ui->monthly_payment_output->setText("Ошибка. проверьте введенные значения");
    ui->overpayment_output->setText("Ошибка. проверьте введенные значения");
    ui->sum_to_pay_output->setText("Ошибка. проверьте введенные значения");
  } else {
    double sum_to_pay = 0.0;
    double overpayment = 0.0;
    double one_month_payment = 0.0;
    if (ui->radioButton_annuity->isChecked()) {
      one_month_payment = annuity_credit(percent, credit_sum, months,
                                         &sum_to_pay, &overpayment);
    } else if (ui->radioButton_differentiate->isChecked()) {
      one_month_payment = differentiate_credit(percent, credit_sum, months,
                                               &sum_to_pay, &overpayment);
    }
    ui->monthly_payment_output->setText(
        QString::number(one_month_payment, 'f', 2));
    ui->overpayment_output->setText(QString::number(overpayment, 'f', 2));
    ui->sum_to_pay_output->setText(QString::number(sum_to_pay, 'f', 2));
  }
}