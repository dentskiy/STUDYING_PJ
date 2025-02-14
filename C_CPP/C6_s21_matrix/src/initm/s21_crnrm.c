#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  status err = STATUS_OK;
  if (rows < 1 || columns < 1) return STATUS_ERROR;
  if (result) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) err = STATUS_ERROR;
    for (int i = 0; !err && i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      err = result->matrix[i] ? STATUS_OK : STATUS_ERROR;
    }
    if (!err) {
      result->rows = rows;
      result->columns = columns;
    }
  } else {
    err = STATUS_ERROR;
  }
  return err;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    if (A->matrix) {
      for (int i = 0; i < A->rows; i++) {
        if (A->matrix[i]) free(A->matrix[i]);
        A->matrix[i] = (void *)0;
      }
      free(A->matrix);
      A->matrix = (void *)0;
    }
    A->rows = 0;
    A->columns = 0;
  }
}