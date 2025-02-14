#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_ITERATOR_TPP_

namespace s21 {

// BaseIterator===========================================================

template <typename Key, typename T>
template <class Iter>
Iter map<Key, T>::BaseIterator<Iter>::operator++() {
  if (goRight()) {
    while (goLeft())
      ;
  } else {
    while (!node->less && goParent())
      ;
    goParent();
  }
  Iter res(node);
  return res;
}

template <typename Key, typename T>
template <class Iter>
Iter map<Key, T>::BaseIterator<Iter>::operator++(int) {
  Iter res(node);
  ++*this;
  return res;
}

template <typename Key, typename T>
template <class Iter>
Iter map<Key, T>::BaseIterator<Iter>::operator--() {
  if (goLeft()) {
    while (goRight())
      ;
  } else {
    while (node->less && goParent())
      ;
    goParent();
  }
  Iter res(node);
  return res;
}

template <typename Key, typename T>
template <class Iter>
Iter map<Key, T>::BaseIterator<Iter>::operator--(int) {
  Iter res(node);
  --*this;
  return res;
}

template <typename Key, typename T>
template <class Iter>
bool map<Key, T>::BaseIterator<Iter>::operator==(iterator it) {
  return node == it.node;
}

template <typename Key, typename T>
template <class Iter>
bool map<Key, T>::BaseIterator<Iter>::operator!=(iterator it) {
  return node != it.node;
}

template <typename Key, typename T>
template <class Iter>
bool map<Key, T>::BaseIterator<Iter>::operator==(const_iterator it) {
  return node == it.node;
}

template <typename Key, typename T>
template <class Iter>
bool map<Key, T>::BaseIterator<Iter>::operator!=(const_iterator it) {
  return node != it.node;
}

template <typename Key, typename T>
template <class Iter>
bool s21::map<Key, T>::BaseIterator<Iter>::goLeft() {
  bool res = node->left != nullptr;
  if (res) node = node->left;
  return res;
}

template <typename Key, typename T>
template <class Iter>
bool s21::map<Key, T>::BaseIterator<Iter>::goRight() {
  bool res = node->right != nullptr;
  if (res) node = node->right;
  return res;
}

template <typename Key, typename T>
template <class Iter>
bool s21::map<Key, T>::BaseIterator<Iter>::goParent() {
  bool res = node->parent != nullptr;
  if (res) node = node->parent;
  return res;
}

// MapIterator============================================================

template <typename Key, typename T>
typename s21::map<Key, T>::reference map<Key, T>::iterator::operator*() {
  return this->node->val;
}
template <typename Key, typename T>
typename s21::map<Key, T>::value_type* map<Key, T>::iterator::operator->() {
  return &this->node->val;
}

// MapConstIterator=======================================================

template <typename Key, typename T>
typename s21::map<Key, T>::const_iterator&
map<Key, T>::const_iterator::operator=(const iterator& it) const {
  this->node = it.node;
  return *this;
}

template <typename Key, typename T>
typename s21::map<Key, T>::const_reference&
map<Key, T>::const_iterator::operator*() const {
  return this->node->val;
}
template <typename Key, typename T>
const typename s21::map<Key, T>::value_type*
map<Key, T>::const_iterator::operator->() const {
  return &this->node->val;
}

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_ITERATOR_TPP_