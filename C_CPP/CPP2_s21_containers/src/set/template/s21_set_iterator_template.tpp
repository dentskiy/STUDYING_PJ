#ifndef CPP2_S21_CONTAINERS_1_SRC_SET_TEMPLATE_S21_SET_ITERATOR_TEMPLATE_H_
#define CPP2_S21_CONTAINERS_1_SRC_SET_TEMPLATE_S21_SET_ITERATOR_TEMPLATE_H_

namespace s21 {

// BaseIterator===========================================================
template <typename T>
template <class Iter>
typename set<T>::Node* set<T>::BaseIterator<Iter>::findPrev(
    typename set<T>::Node* node) {
  if (this->amount != node->amount) {
    ++(this->amount);
    return node;
  }
  if (node->left) {
    node = node->left;
    while (node->right) {
      node = node->right;
    }
    return node;
  }

  while (node->parent && node == node->parent->left) {
    node = node->parent;
  }

  return node->parent;
}

template <typename T>
template <class Iter>
typename set<T>::Node* set<T>::BaseIterator<Iter>::findNext(
    typename set<T>::Node* z) {
  if (this->amount != 1) {
    --(this->amount);
    return z;
  }

  if (z == nullptr) return nullptr;

  if (z->right) {
    z = z->right;
    while (z->left) {
      z = z->left;
    }
    return z;
  }

  while (z->parent && z == z->parent->right) {
    z = z->parent;
  }

  return z->parent;
}

template <typename T>
template <class Iter>
Iter s21::set<T>::BaseIterator<Iter>::operator++() {
  Node* tmp_node = node;
  node = findNext(node);
  int tmp_amount = this->amount;
  Iter res = Iter(node);

  if (node == tmp_node) {
    res.amount = tmp_amount;
  } else if (node != nullptr) {
    this->amount = node->amount;
  }
  return res;
}

template <typename T>
template <class Iter>
Iter set<T>::BaseIterator<Iter>::operator--() {
  Node* tmp_node = node;
  node = findPrev(node);
  int tmp_amount = this->amount;
  Iter res = Iter(node);

  if (node == tmp_node) {
    res.amount = tmp_amount;
  } else if (node != nullptr) {
    this->amount = 1;  // amount default is 1
  }
  return res;
}

template <typename T>
template <class Iter>
Iter set<T>::BaseIterator<Iter>::operator++(int) {
  Iter res(node);
  ++*this;
  return res;
}

template <typename T>
template <class Iter>
Iter set<T>::BaseIterator<Iter>::operator--(int) {
  Iter res(node);
  --*this;
  return res;
}

// setIterator============================================================

template <typename T>
typename s21::set<T>::reference set<T>::iterator::operator*() {
  return this->node->data;
}
template <typename T>
typename s21::set<T>::value_type* set<T>::iterator::operator->() {
  return &this->node->data;
}

// setConstIterator=======================================================

template <typename T>
typename s21::set<T>::const_iterator& set<T>::const_iterator::operator=(
    const iterator& it) const {
  this->node = it.node;
  return *this;
}

template <typename T>
typename s21::set<T>::const_reference& set<T>::const_iterator::operator*()
    const {
  return this->node->data;
}
template <typename T>
const typename s21::set<T>::value_type* set<T>::const_iterator::operator->()
    const {
  return &this->node->data;
}
};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_SET_TEMPLATE_S21_SET_ITERATOR_TEMPLATE_H_
