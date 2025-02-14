#include "s21_calc.h"

int priority(func f);

int s21_sortStation(token_node** list) {
  if (!list || !*list) return NULLPTR;
  status err = OK;
  token_node *stack = (void*)0, *buff = (void*)0, *out = (void*)0;
  while (!err && *list) {
    buff = popNode(list);
    if (buff->arg == NONE || buff->arg == X) {
      setNode(&out, buff);
    } else if (buff->arg <= USUB || buff->arg == OP) {
      pushNode(&stack, buff);
    } else if (buff->arg != ED) {
      while (stack && priority(stack->arg) >= priority(buff->arg))
        setNode(&out, popNode(&stack));
      pushNode(&stack, buff);
    } else {
      removeList(&buff);
      while (stack && stack->arg != OP) setNode(&out, popNode(&stack));
      if (!stack) {
        err = ERROR_ELEM;
      } else {
        buff = popNode(&stack);
        removeList(&buff);
      }
      if (!err && stack && stack->arg <= SQRT) setNode(&out, popNode(&stack));
    }
    buff = (void*)0;
  }
  while (stack) {
    if (stack->arg == OP) err = ERROR_ELEM;
    setNode(&out, popNode(&stack));
  }
  if (!err) {
    *list = out;
    out = (void*)0;
  } else {
    removeList(&out);
    removeList(list);
  }
  return err;
}

int priority(func f) {
  int result = 0;
  switch (f) {
    case OP:
      result = 0;
      break;
    case SUM:
      result = 1;
      break;
    case SUB:
      result = 1;
      break;
    case MULT:
      result = 2;
      break;
    case DIV:
      result = 2;
      break;
    case MOD:
      result = 2;
      break;
    case POW:
      result = 3;
      break;
    default:
      result = 4;
      break;
  }
  return result;
}