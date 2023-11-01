#include <time.h>

#include "s21_smart_calc.h"

#define YEAR 365
#define MONTHS_YEAR 12

double annuity_credit(double percent, double credit_sum, double months,
                      double* sum_to_pay, double* overpayment) {
  double monthly_percent = percent / 12. / 100.;

  double one_month_payment =
      credit_sum *
      (monthly_percent / (1 - pow(1 + monthly_percent, -1 * months)));

  *sum_to_pay = one_month_payment * months;
  *overpayment = *sum_to_pay - credit_sum;
  return one_month_payment;
}

double differentiate_credit(double percent, double credit_sum, double months,
                            double* sum_to_pay, double* overpayment) {
  double monthly_payment = credit_sum / months;
  double remaining_days = 30;
  double percent_sum = 0.,
         result = (credit_sum * (percent / 100) * remaining_days) / YEAR;
  time_t t = time(NULL);
  struct tm c_time = *localtime(&t);
  uint8_t current_month = (c_time.tm_mon + 1) % MONTHS_YEAR;
  int current_year = c_time.tm_year + 1900;
  FILE* fptr = fopen("./differentiate_payments_table.txt", "w+");
  if (fptr != NULL) {
    fprintf(fptr, "    %s\t %10s\t   %10s\t %s\t %s\n", "Месяц",
            "Проценты к выплате", "Основной долг", "Сумма выплаты",
            "Остаток долга");
    for (int i = 0; i < months; i++) {
      if (current_month % MONTHS_YEAR == 1)
        remaining_days = 31;
      else if (current_month % MONTHS_YEAR == 2) {
        if (current_year % 4 != 0 && current_year % 100 != 0) {
          remaining_days = 28;
        } else
          remaining_days = 29;
      } else if (current_month % MONTHS_YEAR == 3)
        remaining_days = 31;
      else if (current_month % MONTHS_YEAR == 4)
        remaining_days = 30;
      else if (current_month % MONTHS_YEAR == 5)
        remaining_days = 31;
      else if (current_month % MONTHS_YEAR == 6)
        remaining_days = 30;
      else if (current_month % MONTHS_YEAR == 7)
        remaining_days = 31;
      else if (current_month % MONTHS_YEAR == 8)
        remaining_days = 31;
      else if (current_month % MONTHS_YEAR == 9)
        remaining_days = 30;
      else if (current_month % MONTHS_YEAR == 10)
        remaining_days = 31;
      else if (current_month % MONTHS_YEAR == 11)
        remaining_days = 30;
      else if (current_month % MONTHS_YEAR == 0) {
        remaining_days = 31;
        current_year++;
      }
      current_month = current_month % 12 != 0 ? current_month % 12 : 12;
      percent_sum = (credit_sum * (percent / 100) * remaining_days) / YEAR;
      credit_sum = credit_sum - monthly_payment;
      *sum_to_pay += percent_sum + monthly_payment;
      *overpayment += percent_sum;
      fprintf(fptr, "%7d\t\t %15.2lf\t\t %12.2lf\t\t %12.2lf\t\t %13.2lf\n",
              current_month + 1, percent_sum, monthly_payment,
              percent_sum + monthly_payment, credit_sum);
      current_month++;
    }
    fclose(fptr);
  } else {
    *sum_to_pay = *overpayment = result = 0;
    *overpayment = percent_sum;
  }
  return monthly_payment;
}