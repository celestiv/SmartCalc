#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR 1
#define YEAR 365
#define MONTH 30
#define WEEK 7
#define CB_KEY_RATE 17

typedef enum {
  s21_number = 0,
  s21_X = 1,

  s21_plus = 2,
  s21_minus = 3,
  s21_multiply = 4,
  s21_division = 5,
  s21_mod = 6,
  s21_pow = 7,

  s21_sin = 8,
  s21_cos = 9,
  s21_tan = 10,
  s21_asin = 11,
  s21_acos = 12,
  s21_atan = 13,
  s21_sqrt = 14,
  s21_ln = 15,
  s21_log = 16,

  s21_left_bracket = 17,
  s21_right_bracket = 18,
  s21_unary_minus = 19
} type_t;

typedef struct rpn_node {
  double value;
  int priority;
  type_t type;
  struct rpn_node* next;
} rpn_node;

typedef enum {
  PRIOR_0,
  PRIOR_1,
  PRIOR_2,
  PRIOR_3,
  PRIOR_4,
  PRIOR_5,
} priorities;

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

// s21_parser.c
void parser(const char* buffer, rpn_node** numbers, rpn_node** operations);
void parse_number(rpn_node** stack, rpn_node** operations, const char* buffer,
                  int* cur_idx);
void parse_punctuations(rpn_node** numbers, rpn_node** operations,
                        char cur_char);
void parse_functions(rpn_node** stack, const char* buffer, int* cur_idx);
double s21_atof(char* src);

// s21_calculator.c
void calculator(rpn_node** elements_stack, double input_X, double* result);

// s21_common.c
double s21_smart_calc(const char* str, double input_X);

void move_between_stack(rpn_node** numbers, rpn_node** operations, char cur_sym,
                        int priority, type_t type);

void push_stack(rpn_node** stack, double value, int priority, type_t type);
void pop_stack(rpn_node** stack);
int is_empty_stack(const rpn_node* node);

int is_digit(int c);
int is_punct(int c);
int is_letter(int c);

// credit.c
double annuity_credit(double percent, double credit_sum, double months,
                      double* sum_to_pay, double* overpayment);
double differentiate_credit(double percent, double credit_sum, double months,
                            double* sum_to_pay, double* overpayment);

// deposit.c
void capitalisation_off(deposit_data* data);
void capitalisation_on(deposit_data* data);
deposit_data* init_data(double* deposit_sum, double* interest, double* days,
                        double* tax_rate, double* output_percents,
                        double* output_taxes, double* output_end_sum,
                        double* percents_per_day);
