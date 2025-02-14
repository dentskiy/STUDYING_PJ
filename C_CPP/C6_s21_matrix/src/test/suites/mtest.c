#include "mtest.h"

/*=====================================================
  Проверка функции s21_create_matrix();
  Mcreate_ok - тест при корректных входных значениях
  Mcreate_err - тест при некрректных входных значениях
=====================================================*/

START_TEST(Mcreate_ok) {
  matrix_t M = {0};
  int flag = s21_create_matrix(5, 6, &M);
  if (!flag) {
    ck_assert_int_eq(M.rows, 5);
    ck_assert_int_eq(M.columns, 6);
    for (int i = 0; i < M.rows; i++)
      for (int j = 0; j < M.columns; j++)
        ck_assert_double_eq(M.matrix[i][j], 0);
    ck_assert_int_eq(flag, STATUS_OK);
  } else
    ck_assert_int_eq(flag, STATUS_ERROR);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(Mcreate_err) {
  matrix_t M = {0};
  int flag = s21_create_matrix(0, 6, &M);
  ck_assert_int_eq(flag, STATUS_ERROR);
  flag = s21_create_matrix(4, -1, &M);
  ck_assert_int_eq(flag, STATUS_ERROR);
  flag = s21_create_matrix(-5, 0, &M);
  ck_assert_int_eq(flag, STATUS_ERROR);
  flag = s21_create_matrix(42, 12, NULL);
  ck_assert_int_eq(flag, STATUS_ERROR);
}
END_TEST

Suite *create_suite() {
  Suite *s = suite_create("create_suite");
  TCase *tc_main = tcase_create("main");
  tcase_add_test(tc_main, Mcreate_ok);
  tcase_add_test(tc_main, Mcreate_err);

  suite_add_tcase(s, tc_main);
  return s;
}

/*==========================================================
  Проверка функции простых функций из папки src/simple_func:
  s21_eq_matrix() : +
  s21_sum_matrix() : -+
  s21_sub_matrix() : -+
  s21_mult_number() : -+
  s21_mult_matrix() : -+
  s21_transpose() : -+
  s21_min() : -+ (не нужна по проекту)
==========================================================*/

START_TEST(eq_matrix_true) {
  matrix_t m1 = {0}, m2 = {0};
  int err = 0;
  err |= s21_create_matrix(1, 6, &m1);
  err |= s21_create_matrix(1, 6, &m2);
  if (!err)
    ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  else
    printf("eq_matrix_true:memory error\n");
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  err = 0;
  err |= s21_eone(5, &m1);
  err |= s21_eone(5, &m2);
  if (!err)
    ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  else
    printf("eq_matrix_true:memory error\n");
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  err = 0;
  err |= s21_nmones(5, 4, &m1);
  err |= s21_nmones(5, 4, &m2);
  if (!err)
    ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  else
    printf("eq_matrix_true:memory error\n");
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(eq_matrix_false) {
  matrix_t m1 = {0}, m2 = {0};
  int err = 0;
  err |= s21_create_matrix(1, 6, &m1);
  err |= s21_nmones(1, 6, &m2);
  if (!err)
    ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  else
    printf("eq_matrix_false:memory error\n");
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  err = 0;
  err |= s21_eone(5, &m1);
  err |= s21_nmones(5, 5, &m2);
  if (!err)
    ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  else
    printf("eq_matrix_false:memory error\n");
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  err = 0;
  err |= s21_nmones(5, 4, &m1);
  err |= s21_nmones(4, 5, &m2);
  if (!err)
    ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  else
    printf("eq_matrix_false:memory error\n");
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(simple_operetions_square1) {
  matrix_t m1 = {0}, m2 = {0}, result = {0};
  int flag = 0;
  int err = s21_nzeros(2, &m1);
  err |= s21_eone(2, &m2);
  if (!err) {
    flag = s21_sum_matrix(&m1, &m2, &result);
    ck_assert_int_eq(flag, STATUS_OK);
    ck_assert_int_eq(s21_eq_matrix(&m2, &result), SUCCESS);
    m1.matrix[0][0] = 1;
    m1.matrix[0][1] = 2;
    m1.matrix[1][0] = 3;
    m1.matrix[1][1] = 4;
    s21_remove_matrix(&result);
    flag = s21_mult_matrix(&m1, &m2, &result);
    ck_assert_int_eq(flag, STATUS_OK);
    ck_assert_int_eq(s21_eq_matrix(&m1, &result), SUCCESS);
    m2.matrix[0][1] = 1;
    m2.matrix[1][0] = 1;
    s21_remove_matrix(&result);
    flag = s21_mult_matrix(&m1, &m2, &result);
    m1.matrix[0][0] = 3;
    m1.matrix[0][1] = 3;
    m1.matrix[1][0] = 7;
    m1.matrix[1][1] = 7;
    ck_assert_int_eq(flag, STATUS_OK);
    ck_assert_int_eq(s21_eq_matrix(&m1, &result), SUCCESS);
    s21_remove_matrix(&result);
    flag = s21_transpose(&m1, &result);
    m1.matrix[0][0] = 3;
    m1.matrix[0][1] = 7;
    m1.matrix[1][0] = 3;
    m1.matrix[1][1] = 7;
    ck_assert_int_eq(flag, STATUS_OK);
    ck_assert_int_eq(s21_eq_matrix(&m1, &result), SUCCESS);
    s21_remove_matrix(&result);
    flag = s21_sub_matrix(&m1, &m2, &result);
    m1.matrix[0][0] = 2;
    m1.matrix[0][1] = 6;
    m1.matrix[1][0] = 2;
    m1.matrix[1][1] = 6;
    ck_assert_int_eq(flag, STATUS_OK);
    ck_assert_int_eq(s21_eq_matrix(&m1, &result), SUCCESS);
    s21_remove_matrix(&result);
    flag = s21_mult_number(&m1, 0.5, &result);
    m1.matrix[0][0] = 1;
    m1.matrix[0][1] = 3;
    m1.matrix[1][0] = 1;
    m1.matrix[1][1] = 3;
    ck_assert_int_eq(flag, STATUS_OK);
    ck_assert_int_eq(s21_eq_matrix(&m1, &result), SUCCESS);
  } else
    printf("simple_operetions: memory error\n");
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(simple_operetions_square2) {
  matrix_t m1 = {0}, m2 = {0}, result = {0}, min = {0}, min_check = {0};
  int flag = 0;
  int err = s21_nmones(3, 3, &m1);
  err |= s21_eone(3, &m2);
  err |= s21_nzeros(2, &min_check);
  if (!err) {
    flag = s21_sum_matrix(&m1, &m2, &result);
    ck_assert_int_eq(flag, STATUS_OK);
    s21_remove_matrix(&m1);
    flag = s21_mult_number(&result, 2, &m1);
    ck_assert_int_eq(flag, STATUS_OK);
    s21_remove_matrix(&result);
    flag = s21_sub_matrix(&m1, &m2, &result);
    ck_assert_int_eq(flag, STATUS_OK);
    flag = s21_minor(&result, 1, 1, &min);
    ck_assert_int_eq(flag, STATUS_OK);
    min_check.matrix[0][0] = 3;
    min_check.matrix[1][0] = 2;
    min_check.matrix[0][1] = 2;
    min_check.matrix[1][1] = 3;
    ck_assert_int_eq(s21_eq_matrix(&min, &min_check), SUCCESS);
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&min_check);
  s21_remove_matrix(&min);
}
END_TEST

Suite *simple_func_suite() {
  Suite *s = suite_create("simple_func_suite");
  TCase *tc_main = tcase_create("main");
  tcase_add_test(tc_main, eq_matrix_true);
  tcase_add_test(tc_main, eq_matrix_false);
  tcase_add_test(tc_main, simple_operetions_square1);
  tcase_add_test(tc_main, simple_operetions_square2);

  suite_add_tcase(s, tc_main);
  return s;
}

/*==========================================================
  Проверка функции простых функций из папки src/common_func:
  int s21_determinant() : +
  int s21_calc_complements() : +
  int s21_inverse_matrix() : +
==========================================================*/

START_TEST(common_func_manual) {
  matrix_t m1 = {0}, inverse = {0}, check = {0};
  double det = 0, det_check = 0;
  int err = s21_nzeros(3, &m1);
  err |= s21_nzeros(3, &check);
  if (!err) {
    m1.matrix[0][0] = 3;
    m1.matrix[0][1] = -5;
    m1.matrix[0][2] = 6;
    m1.matrix[1][0] = -7;
    m1.matrix[1][1] = 8;
    m1.matrix[1][2] = 2;
    m1.matrix[2][0] = 3;
    m1.matrix[2][1] = 1;
    m1.matrix[2][2] = -1;
    ck_assert_int_eq(s21_determinant(&m1, &det), STATUS_OK);
    det_check = -211;
    ck_assert_double_eq(det, det_check);
    ck_assert_int_eq(s21_inverse_matrix(&m1, &inverse), STATUS_OK);
    check.matrix[0][0] = 10. / 211.;
    check.matrix[0][1] = -1. / 211.;
    check.matrix[0][2] = 58. / 211.;
    check.matrix[1][0] = 1. / 211.;
    check.matrix[1][1] = 21. / 211.;
    check.matrix[1][2] = 48. / 211.;
    check.matrix[2][0] = 31. / 211.;
    check.matrix[2][1] = 18. / 211.;
    check.matrix[2][2] = 11. / 211.;
    ck_assert_int_eq(s21_eq_matrix(&inverse, &check), SUCCESS);
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&inverse);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(big_matrix) {
  matrix_t m1 = {0}, m2 = {0}, result = {0}, sum = {0};
  double det = 0;
  ck_assert_int_eq(s21_nmones(7, 7, &m1), STATUS_OK);
  ck_assert_int_eq(s21_eone(7, &m2), STATUS_OK);
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &sum), STATUS_OK);
  ck_assert_int_eq(s21_determinant(&sum, &det), STATUS_OK);
  if (det > EPS || det < -EPS) {
    ck_assert_int_eq(s21_inverse_matrix(&sum, &result), STATUS_OK);
    ck_assert_double_eq_tol(det, 8.0, EPS);
    for (int i = 0; i < result.rows; i++)
      for (int j = 0; j < result.columns; j++)
        if (i == j)
          ck_assert_double_eq_tol(result.matrix[i][j], 7. / 8., EPS);
        else
          ck_assert_double_eq_tol(result.matrix[i][j], -1. / 8., EPS);
  } else
    ck_assert_int_eq(s21_inverse_matrix(&sum, &result), CALCULATION_ERROR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&sum);
}
END_TEST

Suite *common_func_suite() {
  Suite *s = suite_create("common_func_suite");
  TCase *tc_main = tcase_create("main");
  tcase_add_test(tc_main, common_func_manual);
  tcase_add_test(tc_main, big_matrix);

  suite_add_tcase(s, tc_main);
  return s;
}