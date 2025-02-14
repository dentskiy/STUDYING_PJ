#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_calc.h"

#define NCONST 1
#define CONST 0;

int checkX(token_node* list);
int calculation(const token_node* list, double* x, double* y);
double unarCalc(func arg, double val);
double binarCalc(func arg, double left, double right);

int s21_SmartCalc(char* str, char* res, double* x, double* y, double point) {
  if (!str || !res || !x || !y) return NULLPTR;
  int err = OK;
  token_node* list = (void*)0;
  int flag = 0;
  err = s21_getToken(str, &list);
  if (!err) err = s21_sortStation(&list);
  if (!err) {
    flag = checkX(list);
    err = calculation(list, &point, y);
    sprintf(res, "%lf", *y);
    for (int i = 0; !err && i < POINTC; i++)
      if (flag)
        err = calculation(list, x + i, y + i);
      else if (i)
        y[i] = y[i - 1];
  }
  removeList(&list);
  return err;
}

int calculation(const token_node* list, double* x, double* y) {
  if (!list || !x || !y) return NULLPTR;
  status err = OK;
  token_node *stack = (void*)0, *copy = (void*)0;
  while (!err && list) {
    if (list->arg == NONE || list->arg == X) {
      copy = (token_node*)calloc(1, sizeof(token_node));
      if (copy) {
        *copy = *list;
        if (list->arg == X) copy->val = *x;
        pushNode(&stack, copy);
      } else
        err = NULLPTR;
    } else if (list->arg <= USUB) {
      if (stack)
        stack->val = unarCalc(list->arg, stack->val);
      else
        err = ERROR_ELEM;
    } else {
      copy = popNode(&stack);
      if (stack && copy)
        stack->val = binarCalc(list->arg, stack->val, copy->val);
      else
        err = ERROR_ELEM;
      removeList(&copy);
    }
    copy = (void*)0;
    list = list->next;
  }
  if (!err) {
    copy = popNode(&stack);
    if (!stack && copy)
      *y = copy->val;
    else
      err = ERROR_ELEM;
  }
  removeList(&copy);
  removeList(&stack);
  return err;
}

int checkX(token_node* list) {
  int res = 0;
  if (list->arg == X) {
    res = NCONST;
  } else if (!list->next) {
    res = CONST;
  } else {
    res = checkX(list->next);
  }
  return res;
}

double unarCalc(func arg, double val) {
  double res = 0;
  switch (arg) {
    case SIN:
      res = sin(val);
      break;
    case COS:
      res = cos(val);
      break;
    case TAN:
      res = tan(val);
      break;
    case ASIN:
      res = asin(val);
      break;
    case ACOS:
      res = acos(val);
      break;
    case ATAN:
      res = atan(val);
      break;
    case LOG:
      res = log(val);
      break;
    case LOG10:
      res = log10(val);
      break;
    case SQRT:
      res = sqrt(val);
      break;
    case USUB:
      res = -val;
      break;
    default:
      res = val;
      break;
  }
  return res;
}

double binarCalc(func arg, double left, double right) {
  double res = 0;
  switch (arg) {
    case SUM:
      res = left + right;
      break;
    case SUB:
      res = left - right;
      break;
    case MULT:
      res = left * right;
      break;
    case DIV:
      res = left / right;
      break;
    case POW:
      res = pow(left, right);
      break;
    case MOD:
      res = fmod(left, right);
      break;
    default:
      res = left;
      break;
  }
  return res;
}
