#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <stdlib.h>

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum error_status {
  STATUS_OK,
  STATUS_ERROR,
  CALCULATION_ERROR,
} status;

#define EPS 1E-7

#include "common_func/s21_common.h"
#include "initm/s21_crnrm.h"
#include "simple_func/s21_operators.h"

#endif