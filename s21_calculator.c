#include "s21_smart_calc.h"

void calculator(rpn_node** numbers_stack, double input_X, double* result) {
  rpn_node* operations = NULL;
  rpn_node* number1 = NULL;
  rpn_node* number2 = NULL;
  rpn_node* oper = NULL;
  while (!is_empty_stack(*numbers_stack)) {
    number1 = *numbers_stack;
    push_stack(&operations, number1->value, number1->priority, number1->type);
    pop_stack(numbers_stack);
  }
  while (!is_empty_stack(operations)) {
    oper = operations;
    if (oper->type == s21_number) {
      push_stack(numbers_stack, oper->value, oper->priority, oper->type);
    } else if (oper->type == s21_X) {
      push_stack(numbers_stack, input_X, oper->priority, oper->type);
    } else if (oper->type >= 2 && oper->type <= 7) {
      number1 = *numbers_stack;
      number2 = (*numbers_stack)->next;
      if (oper->type == s21_plus) {
        *result = number2->value + number1->value;
      } else if (oper->type == s21_minus) {
        *result = number2->value - number1->value;
      } else if (oper->type == s21_multiply) {
        *result = number2->value * number1->value;
      } else if (oper->type == s21_division) {
        if (number1->value != 0)
          *result = number2->value / number1->value;
        else
          *result = __DBL_MIN__;
      } else if (oper->type == s21_mod) {
        *result = fmod(number2->value, number1->value);
      } else if (oper->type == s21_pow) {
        *result = pow(number2->value, number1->value);
      }
      pop_stack(numbers_stack);
      pop_stack(numbers_stack);
      push_stack(numbers_stack, *result, 0, s21_number);
    } else if (oper->type == s21_unary_minus) {
      (*numbers_stack)->value *= -1;
    } else if (oper->type == s21_sin) {
      (*numbers_stack)->value = sin((*numbers_stack)->value);
    } else if (oper->type == s21_cos) {
      (*numbers_stack)->value = cos((*numbers_stack)->value);
    } else if (oper->type == s21_tan) {
      (*numbers_stack)->value = tan((*numbers_stack)->value);
    } else if (oper->type == s21_asin) {
      (*numbers_stack)->value = asin((*numbers_stack)->value);
    } else if (oper->type == s21_acos) {
      (*numbers_stack)->value = acos((*numbers_stack)->value);
    } else if (oper->type == s21_atan) {
      (*numbers_stack)->value = atan((*numbers_stack)->value);
    } else if (oper->type == s21_sqrt) {
      if ((*numbers_stack)->value >= 0) {
        (*numbers_stack)->value = sqrt((*numbers_stack)->value);
      } else {
        (*numbers_stack)->value = __DBL_MIN__;
      }
    } else if (oper->type == s21_log) {
      if ((*numbers_stack)->value > 0)
        (*numbers_stack)->value = log10((*numbers_stack)->value);
      else
        (*numbers_stack)->value = __DBL_MIN__;
    } else if (oper->type == s21_ln) {
      if ((*numbers_stack)->value > 0)
        (*numbers_stack)->value = log((*numbers_stack)->value);
      else
        (*numbers_stack)->value = __DBL_MIN__;
    }
    pop_stack(&operations);
  }
  double t = (*numbers_stack)->value;
  *result = t;
  pop_stack(numbers_stack);
}
