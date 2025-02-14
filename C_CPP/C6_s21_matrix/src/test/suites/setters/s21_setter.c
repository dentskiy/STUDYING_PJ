#include "s21_setter.h"

int s21_nzeros(int size, matrix_t* A) {
  return s21_create_matrix(size, size, A);
}

int s21_eone(int size, matrix_t* A) {
  int err = s21_create_matrix(size, size, A);
  for (int i = 0; !err && i < size; i++) A->matrix[i][i] = 1.;
  return err;
}

int s21_nmones(int rows, int columns, matrix_t* A) {
  int err = s21_create_matrix(rows, columns, A);
  for (int i = 0; !err && i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) A->matrix[i][j] = 1;
  return err;
}