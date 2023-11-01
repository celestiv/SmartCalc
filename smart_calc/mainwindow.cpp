#include "mainwindow.h"

#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  bracket_count = 0;
  dot_count = 0;
  credit_flag = 0;
  deposit_flag = 0;
  plot_flag = 0;

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));

  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(digits()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(punctuations()));
  connect(ui->pushButton_left_par, SIGNAL(clicked()), this,
          SLOT(punctuations()));
  connect(ui->pushButton_right_par, SIGNAL(clicked()), this,
          SLOT(punctuations()));

  connect(ui->pushButton_all_clear, SIGNAL(clicked()), this,
          SLOT(punctuations()));
  connect(ui->pushButton_backspace, SIGNAL(clicked()), this,
          SLOT(punctuations()));

  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(punctuations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(functions()));

  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(functions()));

  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));

  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));

  connect(ui->pushButton_enter, SIGNAL(clicked()), this, SLOT(calculate()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits() {
  QPushButton *button = (QPushButton *)sender();
  QString label = ui->input_label->text();
  if (MainWindow::conditions(ui) != 5) {
    label = label + button->text();
  }
  ui->input_label->setText(label);
}

void MainWindow::punctuations() {
  QPushButton *button = (QPushButton *)sender();
  QString label = ui->input_label->text();

  if (button->text() == ".") {
    if (MainWindow::conditions(ui) == 2) {
      label = label + ".";
      dot_count++;
    }
    if (MainWindow::conditions(ui) == 0 || MainWindow::conditions(ui) == 3 ||
        MainWindow::conditions(ui) == 4) {
      label = label + "0" + ".";
    }
  } else if (button->text() == "-") {
    if (!ui->input_label->text().endsWith("-") &&
        (MainWindow::conditions(ui) == 0 || MainWindow::conditions(ui) == 2 ||
         MainWindow::conditions(ui) == 4 || MainWindow::conditions(ui) == 5)) {
      label = label + "-";
    }
  } else if (button->text() == "(") {
    if (MainWindow::conditions(ui) == 0 || MainWindow::conditions(ui) == 3 ||
        MainWindow::conditions(ui) == 4) {
      label = label + "(";
      bracket_count++;
    }
  } else if (button->text() == ")") {
    if (MainWindow::conditions(ui) != 0 && MainWindow::conditions(ui) != 4 &&
        bracket_count > 0) {
      label = label + ")";
      bracket_count--;
    }
  } else if (button->text() == "AC") {
    if (label != "") {
      bracket_count = 0;
      label.clear();
    }
    if (ui->result_label->text() != "") {
      ui->result_label->clear();
    }
  } else if (button->text() == "⌫") {
    if (!ui->input_label->text().isEmpty() &&
        ui->input_label->text().endsWith("(")) {
      bracket_count--;
    } else if (!ui->input_label->text().isEmpty() &&
               ui->input_label->text().endsWith(")")) {
      bracket_count++;
    }
    label.chop(1);
  } else {
    label = label + button->text();
  }
  ui->input_label->setText(label);
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  QString label = ui->input_label->text();
  if (MainWindow::is_function(button)) {
    if (MainWindow::conditions(ui) == 0 || MainWindow::conditions(ui) == 3) {
      label = label + button->text() + "(";
    } else if (MainWindow::conditions(ui) == 2) {
      label = label + "*" + button->text() + "(";
    } else if (MainWindow::conditions(ui) == 1) {
      label = label + "0" + "*" + button->text() + "(";
    } else {
      label = label + button->text() + "(";
    }
    bracket_count++;
  } else if (button->text() == "mod") {
    if (MainWindow::conditions(ui) == 1) {
      label = label + "0" + "mod";
    } else if (MainWindow::conditions(ui) == 2) {
      label = label + "mod";
    }
  } else {
    if (MainWindow::conditions(ui) == 1) {
      label = label + "0" + button->text();
    } else if (MainWindow::conditions(ui) == 2 ||
               MainWindow::conditions(ui) == 5) {
      label = label + button->text();
    } else if (MainWindow::conditions(ui) == 3) {
      label = label + "(" + button->text();
      bracket_count++;
    }
  }
  ui->input_label->setText(label);
}

int MainWindow::is_function(QPushButton *button) {
  int result = false;
  if (button->text() == "sin" || button->text() == "asin" ||
      button->text() == "cos" || button->text() == "acos" ||
      button->text() == "tan" || button->text() == "atan" ||
      button->text() == "log" || button->text() == "ln" ||
      button->text() == "sqrt") {
    result = true;
  }
  return result;
}

int MainWindow::conditions(Ui::MainWindow *ui) {
  int result = 0;
  if (ui->input_label->text() == "") {
    result = 0;
  } else if (ui->input_label->text().endsWith(".")) {
    result = 1;
  } else if (ui->input_label->text().endsWith("0") ||
             ui->input_label->text().endsWith("1") ||
             ui->input_label->text().endsWith("2") ||
             ui->input_label->text().endsWith("3") ||
             ui->input_label->text().endsWith("4") ||
             ui->input_label->text().endsWith("5") ||
             ui->input_label->text().endsWith("6") ||
             ui->input_label->text().endsWith("7") ||
             ui->input_label->text().endsWith("8") ||
             ui->input_label->text().endsWith("9") ||
             ui->input_label->text().endsWith("X")) {
    result = 2;
  } else if (ui->input_label->text().endsWith("+") ||
             ui->input_label->text().endsWith("*") ||
             ui->input_label->text().endsWith("/") ||
             ui->input_label->text().endsWith("^")) {
    result = 3;
  } else if (ui->input_label->text().endsWith("(")) {
    result = 4;
  } else if (ui->input_label->text().endsWith(")")) {
    result = 5;
  }
  return result;
}

void MainWindow::calculate() {
  if (ui->input_label->text().length() == 0) {
    ui->result_label->setText("Введите выражение");
  } else if (MainWindow::conditions(ui) == 3) {
    ui->result_label->setText("Ошибка. Операнд в конце выражения");
  } else if (MainWindow::conditions(ui) == 4) {
    ui->result_label->setText("Ошибка. Проверьте скобки");
  } else if (bracket_count != 0) {
    ui->result_label->setText("Ошибка. Проверьте скобки");
  } else {
    QString label = ui->input_label->text();
    std::string std_str = label.toStdString();
    char *c_str = &std_str[0];
    double X_entered = 0.0;
    QString::number(X_entered, 'g', MAX_PRECISION);
    QString x_str = ui->input_X->text();
    if (x_str != "") {
      X_entered = x_str.toDouble();
    } else {
      X_entered = __DBL_MAX__;
    }
    double calc_result = s21_smart_calc(c_str, X_entered);
    if (calc_result != __DBL_MIN__) {
      QString new_label = nullptr;
      new_label = QString::number(calc_result, 'g', MAX_PRECISION);
      if (plot_flag == 0)
        plot = new Plot(this);
      else
        MainWindow::send_data();

      ui->result_label->setText(new_label);
      ui->input_label->setText("");
    } else {
      ui->result_label->setText("Ошибка");
      ui->input_label->setText("");
    }
  }
}

void MainWindow::on_pushButton_credit_clicked() {
  if (credit_flag == 0) credit = new CreditWindow(this);
  credit->show();
  credit_flag = 1;
}

void MainWindow::on_pushButton_deposit_clicked() {
  if (deposit_flag == 0) deposit = new DepositWindow(this);
  deposit->show();
  deposit_flag = 1;
}

void MainWindow::on_pushButton_plot_clicked() {
  if (plot_flag == 0) plot = new Plot(this);
  plot->show();
  plot_flag = 1;
}

void MainWindow::send_data() {
  QString send_string = ui->input_label->text();
  if (send_string.length() != 0) {
    plot->make_plot(send_string);
  }
}
