#include "s21_smart_calc_test.h"

START_TEST(smart_calc_plus) {
    const char* str1 = "2 + 3";
    double check = 2 + 3;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_minus) {
    const char* str1 = "2 - 3";
    double check = 2 - 3;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_multiply) {
    const char* str1 = "2 * 3";
    double check = 2 * 3;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_divide) {
    const char* str1 = "2 / 3";
    double check = 2. / 3.;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_divide_by_zero) {
    const char* str1 = "2. / 0.";
    double check = __DBL_MIN__;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_mod) {
    const char* str1 = "-10mod3";
    double check = fmod(-10, 3);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_pow) {
    const char* str1 = "2 ^ 3";
    double check = pow(2, 3);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST


START_TEST(smart_calc_sin) {
    const char* str1 = "sin(0)";
    double check = sin(0);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_cos) {
    const char* str1 = "cos(1)";
    double check = cos(1);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_tan) {
    const char* str1 = "tan(1)";
    double check = tan(1);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_asin) {
    const char* str1 = "asin(1)";
    double check = asin(1);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_acos) {
    const char* str1 = "acos(0)";
    double check = acos(0);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_atan) {
    const char* str1 = "atan(1)";
    double check = atan(1);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_sqrt) {
    const char* str1 = "sqrt(10)";
    double check = sqrt(10);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_sqrt_negative) {
    const char* str1 = "sqrt(-1)";
    double check = __DBL_MIN__;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_log) {
    const char* str1 = "log(10)";
    double check = log10(10);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST
START_TEST(smart_calc_log_0) {
    const char* str1 = "log(-10)";
    double check = __DBL_MIN__;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_ln) {
    const char* str1 = "ln(10)";
    double check = log(10);
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_ln_0) {
    const char* str1 = "ln(-10)";
    double check = __DBL_MIN__;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_cascade) {
    const char* str1 = "sin(cos(tan(asin(acos(cos(0))))))";
    double check = sin(cos(tan(asin(acos(cos(0))))));
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST


START_TEST(smart_calc_unary_minus) {
    const char* str1 = "-6";
    double check = -6;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST
START_TEST(smart_calc_unary_minus_2) {
    const char* str1 = "-(-6)";
    double check = 6;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

///////////////////////////////////////////////////////
START_TEST(smart_calc_brackets) {
    const char* str1 = "(((((-8)))))";
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(-8, result);
}
END_TEST

START_TEST(smart_calc_empty_str) {
    const char* str1 = "";
    double check = 0.;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq(check, result);
}
END_TEST

START_TEST(smart_calc_x_input) {
    const char* str1 = "5.9 + X";
    double check = 5.9 + 10.4;
    double result = s21_smart_calc(str1, 10.4);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_x_input_2) {
    const char* str1 = "5.9 + 2.888";
    double check = 5.9 + 2.888;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST

START_TEST(smart_calc_priorities) {
    const char* str1 = "8+4*(12.6/5.789)";
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(16.706167, result, EPS);
}
END_TEST

START_TEST(smart_calc_priorities_2) {
    const char* str1 = "8+4*(0.8+12.6/5.789-0.6)";
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(17.506167, result, EPS);
}
END_TEST

START_TEST(smart_calc_priorities_3) {
    const char* str1 = "sin(5)^2+cos(5)^2";
    double check = 1;
    double result = s21_smart_calc(str1, __DBL_MAX__);
    ck_assert_double_eq_tol(check, result, EPS);
}
END_TEST



Suite *smart_calc_backend(void) {
    Suite* s = suite_create("\033[10;35;35m SMART CALC BACKEND \033[0;0;0m\n");
    TCase* tc = tcase_create("smart_calc_backend");

    tcase_add_test(tc, smart_calc_plus);
    tcase_add_test(tc, smart_calc_minus);
    tcase_add_test(tc, smart_calc_multiply);
    tcase_add_test(tc, smart_calc_divide);
    tcase_add_test(tc, smart_calc_divide_by_zero);
    tcase_add_test(tc, smart_calc_mod);
    tcase_add_test(tc, smart_calc_pow);
    tcase_add_test(tc, smart_calc_sin);
    tcase_add_test(tc, smart_calc_cos);
    tcase_add_test(tc, smart_calc_tan);
    tcase_add_test(tc, smart_calc_asin);
    tcase_add_test(tc, smart_calc_acos);
    tcase_add_test(tc, smart_calc_atan);
    tcase_add_test(tc, smart_calc_sqrt);
    tcase_add_test(tc, smart_calc_sqrt_negative);
    tcase_add_test(tc, smart_calc_log);
    tcase_add_test(tc, smart_calc_log_0);
    tcase_add_test(tc, smart_calc_ln);
    tcase_add_test(tc, smart_calc_ln_0);
    tcase_add_test(tc, smart_calc_cascade);

    tcase_add_test(tc, smart_calc_unary_minus);
    tcase_add_test(tc, smart_calc_unary_minus_2);
    tcase_add_test(tc, smart_calc_x_input);
    tcase_add_test(tc, smart_calc_x_input_2);

    tcase_add_test(tc, smart_calc_brackets);
    tcase_add_test(tc, smart_calc_empty_str);

    tcase_add_test(tc, smart_calc_priorities);
    tcase_add_test(tc, smart_calc_priorities_2);
    tcase_add_test(tc, smart_calc_priorities_3);

    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
  Suite* smart_calc_suite = smart_calc_backend();
  SRunner *sr = srunner_create(smart_calc_suite);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
  return 0;
}
