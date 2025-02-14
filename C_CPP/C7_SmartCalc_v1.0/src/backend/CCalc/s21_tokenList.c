#include <stdlib.h>

#include "s21_calc.h"

token_node* popNode(token_node** stack) {
  token_node* buff = *stack;
  if (*stack) *stack = (*stack)->next;
  if (buff) buff->next = NULL;
  return buff;
}

void pushNode(token_node** stack, token_node* elem) {
  elem->next = (*stack);
  (*stack) = elem;
}
void setNode(token_node** list, token_node* elem) {
  if (!*list)
    *list = elem;
  else
    setNode(&((*list)->next), elem);
}

void removeList(token_node** list) {
  if ((*list) && (*list)->next) removeList(&((*list)->next));
  if (*list) free(*list);
  *list = NULL;
}