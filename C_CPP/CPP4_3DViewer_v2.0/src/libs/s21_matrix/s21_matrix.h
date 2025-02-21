#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

#define EPS 1e-7

typedef enum error_matrix {
  OK,
  INCORRECT_MATRIX,
  CALCULATION_ERROR
  // 0 - OK
  // 1 - Ошибка, некорректная матрица
  // 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
  // нельзя провести вычисления и т.д.)
} error_matrix;

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
// int s21_eq_matrix(matrix_t *A, matrix_t *B);
// int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// int s21_transpose(matrix_t *A, matrix_t *result);
// int s21_calc_complements(matrix_t *A, matrix_t *result);
// int s21_determinant(matrix_t *A, double *result);
// int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// //вспомогательные функции
// void diagonal_check(matrix_t *A);
// void swap(matrix_t *A, int ii);
// void method_gaus(matrix_t *A);
// void gauss_method(matrix_t *A);
// void swap_g(matrix_t *A, int i, int j);
// void copy_matrix(matrix_t *A, matrix_t *inv);
// void pred_invers(matrix_t *inv);
// int s21_error(matrix_t *A, matrix_t *B, matrix_t *result);
// int s21_error_two(matrix_t *A, matrix_t *result);
// int s21_error_one(matrix_t *A);
// int s21_error_double(double *value);

#endif