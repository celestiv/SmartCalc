#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDialog>
#define YEAR 365
#define MONTH 30
#define WEEK 7
#define CB_KEY_RATE 17

extern "C" {
#define YEAR 365
#define MONTH 30
#define WEEK 7
#define CB_KEY_RATE 17
typedef struct deposit_data {
  double* deposit_sum;
  double* interest;
  double* days;
  double* tax_rate;
  double* output_percents;  // output values
  double* output_taxes;
  double* output_end_sum;
  double* percents_per_day;
} deposit_data;
void capitalisation_off(deposit_data* data);
void capitalisation_on(deposit_data* data);
deposit_data* init_data(double* deposit_sum, double* interest, double* days,
                        double* tax_rate, double* output_percents,
                        double* output_taxes, double* output_end_sum,
                        double* percents_per_day);
}

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QDialog {
  Q_OBJECT

 public:
  explicit DepositWindow(QWidget* parent = nullptr);
  ~DepositWindow();

 private slots:
  void on_pushButton_close_clicked();
  void on_pushButton_calculate_clicked();

 private:
  Ui::DepositWindow* ui;
  double output_percents = 0.0, output_taxes = 0.0, output_end_sum = 0.0;
};

#endif  // DEPOSITWINDOW_H
