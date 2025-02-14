#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_STACK_S21_STACK_H_

#include "../list/s21_list.h"

namespace s21 {
template <class T>
class stack {
 private:
  list<T> base_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // member func:
  stack() : base_(){};
  stack(std::initializer_list<value_type> const& items) : base_(items){};
  stack(const stack& s) : base_(s.base_){};
  stack(stack&& s) : base_(std::move(s.base_)){};
  ~stack(){};
  stack& operator=(stack&& s);
  stack& operator=(const stack& s);
  // Queue Element access:
  const_reference top() { return base_.back(); };
  // Queue Capacity:
  bool empty() { return base_.empty(); };
  size_type size() { return base_.size(); };
  // Queue Modifiers:
  void push(const_reference value);
  void pop();
  void swap(stack& other);

  template <typename... Args>
  void insert_many_front(Args&&... args);
};
};  // namespace s21

#include "s21_stack.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_STACK_S21_STACK_H_
