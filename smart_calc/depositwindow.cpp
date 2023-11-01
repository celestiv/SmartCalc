#include "depositwindow.h"

#include "ui_depositwindow.h"

DepositWindow::DepositWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::DepositWindow) {
  ui->setupUi(this);
  ui->payments_period_choice->setCurrentIndex(2);
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::on_pushButton_close_clicked() { close(); }

void DepositWindow::on_pushButton_calculate_clicked() {
  double deposit_sum = ui->lineEdit_sum->text().toDouble();
  double interest = ui->lineEdit_interest->text().toDouble();
  double tax_rate = ui->lineEdit_tax_rate->text().toDouble();
  double days = 0.0;
  if (ui->payments_period_choice->currentText() == "Год") {
    days = ui->payments_period_input->text().toDouble() * YEAR;
  } else if (ui->payments_period_choice->currentText() == "Месяц") {
    days = ui->payments_period_input->text().toDouble() * MONTH;
  } else if (ui->payments_period_choice->currentText() == "Неделя") {
    days = ui->payments_period_input->text().toDouble() * WEEK;
  } else {
    days = ui->payments_period_input->text().toDouble();
  }
  int capitalisation = 0;
  if (ui->radioButton_capitalize->isChecked()) {
    capitalisation = 1;
  }
  if (deposit_sum <= 0 || interest <= 0 || days <= 0 ||
      deposit_sum >= __INT64_MAX__ || interest >= 100 || days >= 50 * 365 + 1) {
    ui->output_percents->setText("Ошибка. проверьте введенные значения");
    ui->output_taxes->setText("Ошибка. проверьте введенные значения");
    ui->output_end_sum->setText("Ошибка. проверьте введенные значения");
  } else {
    double output_percents = 0.0, output_taxes = 0.0, output_end_sum = 0.0;
    double percents_per_day = 0.0;
    deposit_data* temp =
        init_data(&deposit_sum, &interest, &days, &tax_rate, &output_percents,
                  &output_taxes, &output_end_sum, &percents_per_day);
    if (temp != nullptr) {
      if (capitalisation == 0) {
        capitalisation_off(temp);
      } else {
        capitalisation_on(temp);
      }
      output_end_sum -= output_taxes;
      ui->output_percents->setText(QString::number(output_percents, 'f', 2));
      ui->output_taxes->setText(QString::number(output_taxes, 'f', 2));
      ui->output_end_sum->setText(QString::number(output_end_sum, 'f', 2));
      free(temp);
    }
  }
}
