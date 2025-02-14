#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_INTERNAL_CLASS_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_INTERNAL_CLASS_TPP_

namespace s21 {

// BaseIterator==========================================================

template <typename T>
template <class Iter>
Iter list<T>::BaseIterator<Iter>::operator++() {
  node = node->next;
  Iter res(node);
  return res;
}

template <typename T>
template <class Iter>
Iter list<T>::BaseIterator<Iter>::operator++(int) {
  Iter res(node);
  node = node->next;
  return res;
}

template <typename T>
template <class Iter>
Iter list<T>::BaseIterator<Iter>::operator--() {
  node = node->back;
  Iter res(node);
  return res;
}

template <typename T>
template <class Iter>
Iter list<T>::BaseIterator<Iter>::operator--(int) {
  Iter res(node);
  node = node->back;
  return res;
}

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_LIST_INTERNAL_CLASS_TPP_