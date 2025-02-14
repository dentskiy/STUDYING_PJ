#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
#define CHECK_ELEM(a, b) (((a) - (b)) < EPS) && (((a) - (b)) > (-EPS))
  int result = SUCCESS;
  if (A && B) {
    if (A->columns != B->columns) result = FAILURE;
    if (A->rows != B->rows) result = FAILURE;
    if (!A->matrix || !B->matrix) result = FAILURE;
    for (int i = 0; result && i < A->rows; i++)
      for (int j = 0; result && j < A->columns; j++)
        result = CHECK_ELEM(A->matrix[i][j], B->matrix[i][j]);
  } else
    result = FAILURE;
#undef CHECK_ELEM
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  status err = STATUS_OK;
  if (!A || !B || !result || !A->matrix || !B->matrix) return STATUS_ERROR;
  if (A->columns != B->columns || A->rows != B->rows) return CALCULATION_ERROR;
  err = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; !err && i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  status err = STATUS_OK;
  if (!A || !B || !result || !A->matrix || !B->matrix) return STATUS_ERROR;
  if (A->columns != B->columns || A->rows != B->rows) return CALCULATION_ERROR;
  err = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; !err && i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  status err = STATUS_OK;
  if (!A || !result || !A->matrix) return STATUS_ERROR;
  err = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; !err && i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;
  return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  status err = STATUS_OK;
  if (!A || !B || !result || !A->matrix || !B->matrix) return STATUS_ERROR;
  if (A->columns != B->rows) return CALCULATION_ERROR;
  err = s21_create_matrix(A->rows, B->columns, result);
  for (int k = 0; !err && k < B->columns; k++) {
    for (int i = 0; i < A->rows; i++) {
      long double sum = 0;
      for (int j = 0; j < A->columns; j++)
        sum += A->matrix[i][j] * B->matrix[j][k];
      result->matrix[i][k] = sum;
    }
  }
  return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  status err = STATUS_OK;
  if (!A || !result || !A->matrix) return STATUS_ERROR;
  err = s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; !err && i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) result->matrix[j][i] = A->matrix[i][j];
  return err;
}

int s21_minor(matrix_t *A, int row, int column, matrix_t *result) {
  status err = STATUS_OK;
  if (!A || !result || !A->matrix) return STATUS_ERROR;
  if (A->columns != A->rows) return CALCULATION_ERROR;
  err = s21_create_matrix(A->rows - 1, A->columns - 1, result);
  for (int i = 0; !err && i < result->rows; i++) {
    int Ai = i < row ? i : i + 1;
    for (int j = 0; j < result->columns; j++) {
      int Aj = j < column ? j : j + 1;
      result->matrix[i][j] = A->matrix[Ai][Aj];
    }
  }
  return err;
}