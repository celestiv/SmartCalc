#ifndef PLOT_H
#define PLOT_H

#include <QDialog>
#include <QVector>

#include "qcustomplot.h"

#define X_START -10
#define X_END 10
#define Y_START -10
#define Y_END 10
#define STEP 0.1
#define RANGE_MIN -1000000
#define RANGE_MAX 1000000

namespace Ui {
class Plot;
}

class Plot : public QDialog {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);
  ~Plot();

 private:
  Ui::Plot *ui;
  double X, y_calculated;
  double x_start, x_end, y_start, y_end;
  int N;
  QVector<double> x, y;

 public slots:
  void make_plot(QString input_string);

 private slots:
  void on_pushButton_replot_clicked();
  void replot();
};

#endif  // PLOT_H
