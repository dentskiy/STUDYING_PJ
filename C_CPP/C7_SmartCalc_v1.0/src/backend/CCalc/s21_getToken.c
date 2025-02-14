#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_calc.h"

void renameFunc(const char* str, char* res);
void setUnar(char* str);
token_node** lastElem(token_node** node);

int s21_getToken(char* str, token_node** start) {
  if (!str || !start) return NULLPTR;
  if (*start) return NO_NULL_LIST;
  status err = OK;
  char func[] = FUNC;
  renameFunc(str, str);
  setUnar(str);
  while (!err && str && *str) {
    if (*str >= '0' && *str <= '9') {
      token_node** elem = lastElem(start);
      *elem = (token_node*)calloc(1, sizeof(token_node));
      if (*elem) {
        (*elem)->arg = NONE;
        (*elem)->next = NULL;
        sscanf(str, "%lf", &((*elem)->val));
      } else
        err = NULLPTR;
    }
    for (int i = 0; i < 2 && *str >= '0' && *str <= '9'; i++) {
      while (*str >= '0' && *str <= '9') str += 1;
      if (*str == '.' && i == 0) str += 1;
    }
    if (*str && strchr(func, *str)) {
      token_node** elem = lastElem(start);
      *elem = (token_node*)calloc(1, sizeof(token_node));
      if (*elem) {
        (*elem)->arg = *str++;
        (*elem)->next = NULL;
        (*elem)->val = 0. / 0.;
      } else
        err = NULLPTR;
    } else if (*str == 'x') {
      token_node** elem = lastElem(start);
      *elem = (token_node*)calloc(1, sizeof(token_node));
      if (*elem) {
        (*elem)->arg = X;
        (*elem)->next = NULL;
        (*elem)->val = 0. / 0.;
        str++;
      } else
        err = NULLPTR;
    } else if (*str) {
      err = ERROR_ELEM;
    }
  }
  if (err) removeList(start);
  return err;
}

void renameFunc(const char* str, char* res) {
  while (str && res && *str) {
    if (!strncmp(str, "sin", 3)) {
      *res++ = SIN;
      str += 3;
    } else if (!strncmp(str, "cos", 3)) {
      *res++ = COS;
      str += 3;
    } else if (!strncmp(str, "tan", 3)) {
      *res++ = TAN;
      str += 3;
    } else if (!strncmp(str, "asin", 3)) {
      *res++ = ASIN;
      str += 4;
    } else if (!strncmp(str, "acos", 3)) {
      *res++ = ACOS;
      str += 4;
    } else if (!strncmp(str, "atan", 4)) {
      *res++ = ATAN;
      str += 4;
    } else if (!strncmp(str, "sqrt", 4)) {
      *res++ = SQRT;
      str += 4;
    } else if (!strncmp(str, "ln", 2)) {
      *res++ = LOG;
      str += 2;
    } else if (!strncmp(str, "log", 3)) {
      *res++ = LOG10;
      str += 3;
    } else if (!strncmp(str, "mod", 3)) {
      *res++ = MOD;
      str += 3;
    } else {
      *res++ = *str++;
    }
  }
  *res = '\0';
}

void setUnar(char* str) {
  int flag = 1;
  for (; str && *str; str++) {
    switch (*str) {
      case SUM:
        if (flag) *str = USUM;
        flag = 0;
        break;
      case SUB:
        if (flag) *str = USUB;
        flag = 0;
        break;
      case OP:
        flag = 1;
        break;
      default:
        flag = 0;
    }
  }
}

token_node** lastElem(token_node** node) {
  if (!(*node)) return node;
  return lastElem(&((*node)->next));
}
