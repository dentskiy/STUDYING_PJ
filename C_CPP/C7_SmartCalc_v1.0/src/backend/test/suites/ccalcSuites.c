#include <math.h>

#include "test.h"

/*======================================================
Начало положено: SmartCalc:
s21_getToken() : status : SUCCESS
s21_sortStation() : status : SUCCESS
s21_SmartCalc() : status : SUCCES
======================================================*/

// s21_getToken()---------------------------------------|

START_TEST(get_token_list_OK1) {
  char str[] = "sin(5)*2";
  token_node *list = (void *)0;
  int counter = 0;
  ck_assert_int_eq(s21_getToken(str, &list), OK);
  while (list) {
    token_node *copy = popNode(&list);
    counter++;
    removeList(&copy);
  }
  ck_assert_int_eq(counter, 6);
}
END_TEST

START_TEST(get_token_list_OK2) {
  char str[] = "sin+cos+tan+asin+acos+atan+sqrt+ln+log+mod";
  token_node *list = (void *)0;
  int counter = 0;
  ck_assert_int_eq(s21_getToken(str, &list), OK);
  while (list) {
    token_node *copy = popNode(&list);
    counter++;
    removeList(&copy);
  }
  ck_assert_int_eq(counter, 19);
}
END_TEST

START_TEST(get_token_list_OK3) {
  char str[] = "+sin(-x^(2))";
  token_node *list = (void *)0;
  int counter = 0;
  ck_assert_int_eq(s21_getToken(str, &list), OK);
  while (list) {
    token_node *copy = popNode(&list);
    counter++;
    removeList(&copy);
  }
  ck_assert_int_eq(counter, 10);
}
END_TEST

START_TEST(get_token_list_ERROR) {
  char str[] = "251.51.554";
  token_node *list = (void *)0;
  ck_assert_int_eq(s21_getToken(str, &list), ERROR_ELEM);
  ck_assert_ptr_null(list);
}
END_TEST

// s21_sortStation()------------------------------------|

START_TEST(sort_station_OK1) {
  char str[] = "sin(5)*2";
  token_node *list = (void *)0;

  func array[] = {NONE, SIN, NONE, MULT};

  ck_assert_int_eq(s21_getToken(str, &list), OK);
  ck_assert_int_eq(s21_sortStation(&list), OK);
  for (int i = 0; i < 4; i++) {
    token_node *copy = popNode(&list);
    ck_assert_int_eq(copy->arg, array[i]);
    removeList(&copy);
  }
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(sort_station_OK2) {
  char str[] = "2/(3+2)*5";
  token_node *list = (void *)0;

  func array[] = {NONE, NONE, NONE, SUM, DIV, NONE, MULT};

  ck_assert_int_eq(s21_getToken(str, &list), OK);
  ck_assert_int_eq(s21_sortStation(&list), OK);
  for (int i = 0; i < 7; i++) {
    token_node *copy = popNode(&list);
    ck_assert_int_eq(copy->arg, array[i]);
    removeList(&copy);
  }
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(sort_station_ERROR1) {
  char str[] = "(3mod2";
  token_node *list = (void *)0;

  ck_assert_int_eq(s21_getToken(str, &list), OK);
  ck_assert_int_eq(s21_sortStation(&list), ERROR_ELEM);

  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(sort_station_ERROR2) {
  char str[] = "5-6^x)";
  token_node *list = (void *)0;

  ck_assert_int_eq(s21_getToken(str, &list), OK);
  ck_assert_int_eq(s21_sortStation(&list), ERROR_ELEM);

  ck_assert_ptr_null(list);
}
END_TEST

// s21_SmartCalc()-------------------------------------|

START_TEST(SmartCalc_OK1) {
  double x[POINTC] = {0}, y[POINTC] = {0};
  char str[] = "tan(x)/(x^2+1)", res[15] = {0};
  for (int i = 0; i < POINTC; i++) x[i] = -5. + 0.1 * i;
  ck_assert_int_eq(s21_SmartCalc(str, res, x, y, 1.0), OK);
  ck_assert_str_eq(res, "0.778704");
  for (int i = 0; i < POINTC; i++)
    ck_assert_double_eq_tol(y[i], tan(x[i]) / (pow(x[i], 2) + 1), 1E-7);
}
END_TEST

START_TEST(SmartCalc_OK2) {
  double x[POINTC] = {0}, y[POINTC] = {0};
  char str[] = "sin(3)*2-(-ln(1)+log(1))mod30.5+(+cos(acos(1)))", res[15] = {0};
  ck_assert_int_eq(s21_SmartCalc(str, res, x, y, 0.0), OK);
  ck_assert_str_eq(res, "1.282240");
}
END_TEST

START_TEST(SmartCalc_ERROR1) {
  double x[POINTC] = {0}, y[POINTC] = {0};
  char str[] = "asin(atan(6))*sqrt()", res[15] = {0};
  ck_assert_int_eq(s21_SmartCalc(str, res, x, y, 0.0), ERROR_ELEM);
}
END_TEST

START_TEST(SmartCalc_ERROR2) {
  double x[POINTC] = {0}, y[POINTC] = {0};
  char str[] = "sqrt()", res[15] = {0};
  ck_assert_int_eq(s21_SmartCalc(str, res, x, y, 0.0), ERROR_ELEM);
}
END_TEST

Suite *SmartCalc_suite() {
  Suite *s = suite_create("SmartCalc");
  TCase *tc_main = tcase_create("main");
  tcase_add_test(tc_main, get_token_list_OK1);
  tcase_add_test(tc_main, get_token_list_OK2);
  tcase_add_test(tc_main, get_token_list_OK3);
  tcase_add_test(tc_main, get_token_list_ERROR);

  tcase_add_test(tc_main, sort_station_OK1);
  tcase_add_test(tc_main, sort_station_OK2);
  tcase_add_test(tc_main, sort_station_ERROR1);
  tcase_add_test(tc_main, sort_station_ERROR2);

  tcase_add_test(tc_main, SmartCalc_OK1);
  tcase_add_test(tc_main, SmartCalc_OK2);
  tcase_add_test(tc_main, SmartCalc_ERROR1);
  tcase_add_test(tc_main, SmartCalc_ERROR2);

  suite_add_tcase(s, tc_main);
  return s;
}

/*======================================================
Доп. часть: BankCalc:
s21_creditA() : status : SUCCESS
s21_creditDif() : status : SUCCESS
s21_deposit() : status : SUCCESS
======================================================*/

START_TEST(credit_ALL) {
  ck_assert_int_eq(s21_creditA(300000, 12, 16), 27219);
  ck_assert_int_eq(s21_creditA(300000, 9, 16), 35595);
  ck_assert_int_eq(s21_creditA(300000, 12, 7), 25958);
  ck_assert_int_eq(s21_creditDif(300000, 12, 16), 326000);
}
END_TEST

START_TEST(deposit_calc) {
  deposit dep = {0};
  dep.sum = 100000;
  dep.pc = 12;
  dep.pn = 13;
  dep.month = 12;
  dep.kflag = 1;
  dep.period = 0;
  dep.perup = 0;
  dep.sumup = 0;
  dep.result = dep.sum;
  dep.tax = 0.;
  s21_deposit(&dep);
  ck_assert_double_eq_tol(dep.result, 112656, dep.result / 1000);
}

Suite *BankCalc_suite() {
  Suite *s = suite_create("BankCalc");
  TCase *tc_main = tcase_create("main");
  tcase_add_test(tc_main, credit_ALL);
  tcase_add_test(tc_main, deposit_calc);

  suite_add_tcase(s, tc_main);
  return s;
}