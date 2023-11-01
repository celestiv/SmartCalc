#include "s21_smart_calc.h"

void capitalisation_off(deposit_data* data) {
  for (double i = 0.0; i < *data->days; i++) {
    *data->output_percents +=
        *data->deposit_sum * *data->interest / 100.0 / 365.0;
  }
  *data->output_end_sum = *data->output_percents + *data->deposit_sum;
  if (*data->output_percents > CB_KEY_RATE / 100.0 * 1000000.0) {
    *data->output_taxes =
        *data->tax_rate / 100.0 *
        (*data->output_percents - CB_KEY_RATE / 100.0 * 1000000.0);
    *data->output_percents -= *data->output_taxes;
    *data->output_end_sum -= *data->output_taxes;
  }
}

void capitalisation_on(deposit_data* data) {
  double percents_per_day = 0.0, percents = 0.0;
  for (double i = 0; i < *data->days; i++) {
    percents_per_day = *data->deposit_sum * *data->interest / 100 / 365;
    percents += percents_per_day;
    *data->deposit_sum = *data->deposit_sum + percents_per_day;
  }
  *data->output_percents = percents;
  if (*data->output_percents > CB_KEY_RATE / 100 * 1000000) {
    *data->output_taxes =
        *data->tax_rate / 100 *
        (*data->output_percents - CB_KEY_RATE / 100 * 1000000);
    *data->output_percents -= *data->output_taxes;
    *data->output_end_sum = *data->deposit_sum - *data->output_taxes;
  } else {
    *data->output_percents = percents;
    *data->output_end_sum = *data->deposit_sum;
  }
}

deposit_data* init_data(double* deposit_sum, double* interest, double* days,
                        double* tax_rate, double* output_percents,
                        double* output_taxes, double* output_end_sum,
                        double* percents_per_day) {
  deposit_data* temp = calloc(1, sizeof(deposit_data));
  temp->deposit_sum = deposit_sum;
  temp->interest = interest;
  temp->days = days;
  temp->tax_rate = tax_rate;
  temp->output_percents = output_percents;
  temp->output_taxes = output_taxes;
  temp->output_end_sum = output_end_sum;
  return temp;
}
