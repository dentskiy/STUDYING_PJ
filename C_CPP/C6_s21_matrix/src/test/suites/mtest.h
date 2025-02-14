#ifndef S21_MTEST
#define S21_MTEST
#include <check.h>
#include <stdio.h>

#include "../../s21_matrix.h"
#include "setters/s21_setter.h"

Suite* create_suite();
Suite* simple_func_suite();
Suite* common_func_suite();

#endif