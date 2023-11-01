#include "plot.h"

#include "ui_plot.h"

extern "C" {
double s21_smart_calc(const char *str, double input_X);
}

Plot::Plot(QWidget *parent) : QDialog(parent), ui(new Ui::Plot) {
  ui->setupUi(this);

  ui->lineEdit_x1->setRange(RANGE_MIN, RANGE_MAX);
  ui->lineEdit_y1->setRange(RANGE_MIN, RANGE_MAX);

  ui->lineEdit_x1->setValue(X_START);
  ui->lineEdit_x2->setValue(X_END);
  ui->lineEdit_y1->setValue(Y_START);
  ui->lineEdit_y2->setValue(Y_END);

  ui->widget->addGraph();
}

Plot::~Plot() { delete ui; }

void Plot::make_plot(QString input_string) {
  ui->expression_label->setText(input_string);
  Plot::replot();
}

void Plot::on_pushButton_replot_clicked() { Plot::replot(); }

void Plot::replot() {
  QString input_expression = ui->expression_label->text();
  std::string std_expression = input_expression.toStdString();
  char *c_expression = &std_expression[0];
  if (c_expression) {
    x_start = ui->lineEdit_x1->text().toDouble();
    x_end = ui->lineEdit_x2->text().toDouble();
    y_start = ui->lineEdit_y1->text().toDouble();
    y_end = ui->lineEdit_y2->text().toDouble();

    if (x_end <= x_start) x_start = x_end + 10;
    if (y_end <= y_start) y_start = y_end + 10;

    ui->widget->xAxis->setRange(x_start, x_end);
    ui->widget->yAxis->setRange(y_start, y_end);
    N = (x_end - x_start) / STEP + 2;

    x.clear();
    y.clear();
    for (X = x_start; X <= x_end; X += STEP) {
      x.push_back(X);
      y_calculated = s21_smart_calc(c_expression, X);
      y.push_back(y_calculated);
      X += STEP;
    }
    if (ui->widget) {
      ui->widget->graph(0)->setData(x, y);
      ui->widget->replot();
    }
  }
}