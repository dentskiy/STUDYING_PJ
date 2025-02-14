#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  status err = STATUS_OK;
  if (!A || !A->matrix || !result) return STATUS_ERROR;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  *result = 0;
  double elem = 0;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result = A->matrix[0][0] * A->matrix[1][1];
    *result -= A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; !err && i < A->rows; i++) {
      matrix_t minor = {0};
      err = s21_minor(A, 0, i, &minor);
      if (!err) err = s21_determinant(&minor, &elem);
      if (!err) *result += (i % 2 ? -1 : 1) * A->matrix[0][i] * elem;
      s21_remove_matrix(&minor);
    }
  }
  return err;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  status err = STATUS_OK;
  if (!A || !A->matrix || !result) return STATUS_ERROR;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  err = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; !err && i < result->rows; i++) {
    for (int j = 0; !err && j < result->columns; j++) {
      matrix_t minor = {0};
      err = s21_minor(A, i, j, &minor);
      if (!err) err = s21_determinant(&minor, result->matrix[i] + j);
      result->matrix[i][j] *= (i + j) % 2 ? -1 : 1;
      s21_remove_matrix(&minor);
    }
  }
  return err;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  status err = STATUS_OK;
  if (!A || !A->matrix || !result) return STATUS_ERROR;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  double det = 0;
  err = s21_determinant(A, &det);
  if (det < EPS && det > -EPS) {
    err = CALCULATION_ERROR;
  } else {
    matrix_t M = {0}, MT = {0};
    err = s21_calc_complements(A, &M);
    if (!err) err = s21_transpose(&M, &MT);
    if (!err) err = s21_mult_number(&MT, 1 / det, result);
    s21_remove_matrix(&M);
    s21_remove_matrix(&MT);
  }
  return err;
}