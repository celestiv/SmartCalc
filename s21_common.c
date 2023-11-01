#include "s21_smart_calc.h"

/// @brief основная функция, которая делает вычисления на основе двух стеков
/// и складывает результат в переменную типа double
/// @param str
/// @return возвращает результат число тип double
double s21_smart_calc(const char* str, double input_X) {
  // puts(str);
  rpn_node* numbers = NULL;
  rpn_node* operations = NULL;
  double result = 0.;
  if (strcmp(str, "")) {
    parser(str, &numbers, &operations);
    if (strchr(str, 'X') != NULL) {
      if (input_X != __DBL_MAX__) {
        calculator(&numbers, input_X, &result);
      } else {
        result = 0.0;
      }
    } else {
      calculator(&numbers, __DBL_MAX__, &result);
    }
  } else {
    result = 0.;
  }
  return result;
}

///////////////////////////////////////   Функции для работы со стеком

void push_stack(rpn_node** stack, double value, int priority, type_t type) {
  rpn_node* new_node = (rpn_node*)malloc(sizeof(rpn_node));
  new_node->value = value;
  new_node->priority = priority;
  new_node->type = type;
  new_node->next = *stack;
  *stack = new_node;
}

void pop_stack(rpn_node** stack) {
  if (*stack != NULL) {
    rpn_node* tmp = (*stack);
    (*stack) = tmp->next;
    free(tmp);
  }
}

int is_empty_stack(const rpn_node* node) { return (node == NULL); }

void move_between_stack(rpn_node** numbers, rpn_node** operations, char cur_sym,
                        int priority, type_t type) {
  if (is_empty_stack(*operations) ||
      (!is_empty_stack(*operations) && (*operations)->value == '(')) {
    push_stack(operations, cur_sym, priority, type);
  } else if (!is_empty_stack(*operations) &&
             priority > (*operations)->priority) {
    push_stack(operations, cur_sym, priority, type);
  } else {
    while (
        !is_empty_stack(*operations) &&
        ((*operations)->value == '(' || priority < (*operations)->priority)) {
      if ((*operations)->value == '(') {
        pop_stack(operations);
        if ((*operations)->value == '~') {
          push_stack(numbers, (*operations)->value, (*operations)->priority,
                     (*operations)->type);
          pop_stack(operations);
        }
      } else {
        push_stack(numbers, (*operations)->value, (*operations)->priority,
                   (*operations)->type);
        pop_stack(operations);
      }
    }
    push_stack(operations, cur_sym, priority, type);
  }
}

//////////////////////////////////////    Функции математики

/// @brief проверка является ли символ цифрой от 0 до 9
/// @param
/// @return 1 - true, 0 - false
int is_digit(int c) { return c >= '0' && c <= '9'; }

/// @brief проверка является ли символ арифметическим действием + - * / ^
/// либо скобкой ( )
/// @param
/// @return 1 - true, 0 - false
int is_punct(int c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ||
          c == '(' || c == ')' || c == '~');
}

int is_letter(int c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
