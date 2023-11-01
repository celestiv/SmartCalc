#include "s21_smart_calc.h"

/// @brief разбирает строку и складывает значения в структуры для хранения
/// @param buffer  исходная строка
/// @param numbers очередь на основе односвязного списка ждя хранения чисел
/// @param operations_stack стэк на основе односвязного
/// списка для хранения математических операторов
void parser(const char* buffer, rpn_node** numbers,
            rpn_node** operations_stack) {
  for (int i = 0; buffer[i] != '\0'; i++) {
    char current_char = buffer[i];
    if (is_digit(current_char)) {
      parse_number(numbers, operations_stack, buffer, &i);
    } else if (current_char == 'X') {
      push_stack(numbers, 0, PRIOR_0, s21_X);
    } else if (is_punct(current_char)) {
      parse_punctuations(numbers, operations_stack, current_char);
    } else if (is_letter(current_char)) {
      parse_functions(operations_stack, buffer, &i);
    } else {
      continue;
    }
  }
  while (!is_empty_stack(*operations_stack)) {
    push_stack(numbers, (*operations_stack)->value,
               (*operations_stack)->priority, (*operations_stack)->type);
    pop_stack(operations_stack);
  }
}

void parse_number(rpn_node** numbers, rpn_node** operations, const char* buffer,
                  int* cur_idx) {
  char temp[256] = "\0";
  int flag = 1;
  for (int j = 0; flag == 1; j++) {
    if (is_digit(buffer[*cur_idx]) || buffer[*cur_idx] == '.') {
      temp[j] = buffer[(*cur_idx)];
      (*cur_idx)++;
    } else {
      flag = 0;
    }
  }
  (*cur_idx)--;
  if ((!is_empty_stack(*numbers) && (*numbers)->value == '~') ||
      (!is_empty_stack(*operations) && (*operations)->value == '(' &&
       !is_empty_stack(*numbers) && (*numbers)->value == '~')) {
    pop_stack(numbers);
    push_stack(numbers, -1 * s21_atof(temp), 0, s21_number);
  } else {
    push_stack(numbers, s21_atof(temp), 0, s21_number);
  }
}

void parse_punctuations(rpn_node** numbers, rpn_node** operations_stack,
                        char cur_char) {
  if (cur_char == '+') {
    move_between_stack(numbers, operations_stack, '+', PRIOR_1, s21_plus);
  } else if (cur_char == '-') {
    if (is_empty_stack(*operations_stack) && is_empty_stack(*numbers)) {
      push_stack(operations_stack, '~', PRIOR_5, s21_unary_minus);
    } else if (!is_empty_stack(*operations_stack) &&
               (*operations_stack)->value == '(') {
      push_stack(numbers, '~', PRIOR_5, s21_unary_minus);
      // } else if (!is_empty_stack(*operations_stack) &&
      // (*operations_stack)->type > s21_X) {

      //   push_stack(numbers, '~', PRIOR_5, s21_unary_minus);
    } else {
      move_between_stack(numbers, operations_stack, '-', PRIOR_1, s21_minus);
    }
  } else if (cur_char == '*') {
    move_between_stack(numbers, operations_stack, '*', PRIOR_2, s21_multiply);

  } else if (cur_char == '/') {
    move_between_stack(numbers, operations_stack, '/', PRIOR_2, s21_division);

  } else if (cur_char == '^') {
    move_between_stack(numbers, operations_stack, '^', PRIOR_3, s21_pow);

  } else if (cur_char == '(') {
    push_stack(operations_stack, '(', PRIOR_5, s21_left_bracket);

  } else if (cur_char == ')') {
    while (!is_empty_stack(*operations_stack) &&
           (*operations_stack)->value != '(') {
      push_stack(numbers, (*operations_stack)->value,
                 (*operations_stack)->priority, (*operations_stack)->type);
      pop_stack(operations_stack);
    }
    pop_stack(operations_stack);
  }
}

void parse_functions(rpn_node** stack, const char* buffer, int* cur_idx) {
  char temp[255] = {0};
  int flag = 1;
  for (int j = 0; flag == 1; j++) {
    if (is_letter(buffer[*cur_idx]) || buffer[*cur_idx] == '.') {
      temp[j] = buffer[(*cur_idx)];
      (*cur_idx)++;
    } else {
      flag = 0;
    }
  }
  (*cur_idx)--;
  if (strstr("sin", temp)) {
    push_stack(stack, 0, PRIOR_4, s21_sin);
  } else if (strstr("cos", temp)) {
    push_stack(stack, 0, PRIOR_4, s21_cos);
  } else if (strstr("tan", temp)) {
    push_stack(stack, 0, PRIOR_4, s21_tan);
  } else if (strstr("asin", temp)) {
    push_stack(stack, 0, PRIOR_4, s21_asin);
  } else if (strstr("acos", temp)) {
    push_stack(stack, 0, PRIOR_4, s21_acos);
  } else if (strstr("atan", temp)) {
    push_stack(stack, 0, PRIOR_4, s21_atan);
  } else if (strstr("log", temp)) {
    push_stack(stack, 0, PRIOR_4, s21_log);
  } else if (strstr("ln", temp)) {
    push_stack(stack, 0, PRIOR_4, s21_ln);
  } else if (strstr("sqrt", temp)) {
    push_stack(stack, 0, PRIOR_3, s21_sqrt);
  } else if (strstr("mod", temp)) {
    push_stack(stack, 0, PRIOR_2, s21_mod);
  }
}

double s21_atof(char* src) {
  if (src == NULL) return 0.0;
  double result = 0.;
  int decimal_flag = 0;
  int decimal_places = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    if (src[i] == '.') {
      decimal_flag = 1;
      continue;
    }
    if (src[i] >= '0' && src[i] <= '9') {
      result = result * 10 + src[i] - '0';
      if (decimal_flag == 1) {
        decimal_places++;
      }
    }
  }
  if (decimal_flag == 1) {
    while (decimal_places != 0) {
      decimal_places--;
      result /= 10;
    }
  }
  return result;
}