#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  error_matrix error = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    error = INCORRECT_MATRIX;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix =
        (double **)calloc(rows, sizeof(double *) + columns * sizeof(double));
    if (result->matrix != NULL) {
      result->matrix[0] = (double *)result->matrix + rows;
      for (int i = 1; i < rows; i++) {
        result->matrix[i] = result->matrix[0] + i * columns;
      }
    }
  }
  return error;
}
