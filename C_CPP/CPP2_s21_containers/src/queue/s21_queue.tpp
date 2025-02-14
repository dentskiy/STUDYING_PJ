#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_S21_QUEUE_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_S21_QUEUE_TPP_

namespace s21 {
template <typename T>
queue<T>& queue<T>::operator=(queue<T>&& q) {
  if (this != &q) {
    base_ = std::move(q.base_);
  }
  return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(const queue<T>& q) {
  if (this != &q) {
    queue<T> copy(q);
    *this = std::move(copy);
  }
  return *this;
}

template <typename T>
void queue<T>::push(const_reference val) {
  base_.push_back(val);
}

template <typename T>
void queue<T>::pop() {
  base_.pop_front();
}

template <typename T>
void queue<T>::swap(queue<T>& q) {
  if (this != &q) base_.swap(q.base_);
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  for (auto arg : {args...}) {
    push(arg);
  }
}

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_S21_QUEUE_TPP_