#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_STACK_S21_STACK_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_S21_STACK_S21_STACK_TPP_

namespace s21 {
template <typename T>
typename s21::stack<T>& stack<T>::operator=(stack<T>&& s) {
  if (this != &s) base_ = std::move(s.base_);
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& s) {
  if (this != &s) {
    stack<T> copy(s);
    *this = std::move(copy);
  }
  return *this;
}

template <typename T>
void stack<T>::push(const_reference val) {
  base_.push_back(val);
}

template <typename T>
void stack<T>::pop() {
  base_.pop_back();
}

template <typename T>
void stack<T>::swap(stack<T>& s) {
  if (this != &s) base_.swap(s.base_);
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args&&... args) {
  for (auto& arg : {args...}) {
    push(arg);
  }
}

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_STACK_S21_STACK_TPP_
