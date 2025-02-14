#ifndef CPP2_S21_CONTAINERS_1_SRC_SET_TEMPLATE_S21_SET_TEMPLATE_H_
#define CPP2_S21_CONTAINERS_1_SRC_SET_TEMPLATE_S21_SET_TEMPLATE_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
// set member functions
template <typename T>
set<T>::set() : root_{nullptr}, len{} {}

template <typename T>
set<T>::set(std::initializer_list<T> const& items) : set() {
  for (auto it = items.begin(); it != items.end(); it++) innerInsert(*it);
}

template <typename T>
set<T>::set(const set& s) : set() {
  for (auto it = s.begin(); it != s.end(); it++) innerInsert(*it);
}

template <typename T>
set<T>::set(set&& s) : root_{s.root_}, len{s.len} {
  s.root_ = nullptr;
  s.len = 0;
}

template <typename T>
set<T>& set<T>::operator=(const set& s) {
  if (this != &s) {
    set copy(s);
    *this = std::move(copy);
  }
  return *this;
}

template <typename T>
set<T>& set<T>::operator=(set&& s) {
  if (this != &s) {
    clear(root_);
    root_ = s.root_;
    len = s.len;
    s.root_ = nullptr;
    s.len = 0;
  }
  return *this;
}

template <typename T>
set<T>::~set() {
  clear(root_);
}

template <typename T>
int set<T>::height(Node* node) const {
  return node ? node->height : 0;
}

template <typename T>
int set<T>::balanceFactor(Node* node) const {
  return node ? height(node->left) - height(node->right) : 0;
}

template <typename T>
void set<T>::updateHeight(Node* node) {
  node->height = 1 + std::max(height(node->left), height(node->right));
}

template <typename T>
typename set<T>::Node* set<T>::rotateRight(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;

  x->right = y;
  y->left = T2;

  if (T2) T2->parent = y;
  x->parent = y->parent;
  y->parent = x;

  updateHeight(y);
  updateHeight(x);

  return x;
}

template <typename T>
typename set<T>::Node* set<T>::rotateLeft(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;

  y->left = x;
  x->right = T2;

  if (T2) T2->parent = x;
  y->parent = x->parent;
  x->parent = y;

  updateHeight(x);
  updateHeight(y);

  return y;
}

template <typename T>
void set<T>::innerInsert(T value) {
  root_ = innerInsert(root_, value, nullptr);
}

template <typename T>
typename set<T>::Node* set<T>::innerInsert(Node* node, T value, Node* parent) {
  if (node == nullptr) {
    ++len;
    return new Node(value, parent);
  }

  if (value < node->data) {
    node->left = innerInsert(node->left, value, node);
  } else if (value > node->data) {
    node->right = innerInsert(node->right, value, node);
  } else {
    return node;  // Duplicate values are not innerInserted
  }

  updateHeight(node);

  int balance = balanceFactor(node);

  // Left Left Case
  if (balance > 1 && value < node->left->data) {
    return rotateRight(node);
  }

  // Right Right Case
  if (balance < -1 && value > node->right->data) {
    return rotateLeft(node);
  }

  // Left Right Case
  if (balance > 1 && value > node->left->data) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  // Right Left Case
  if (balance < -1 && value < node->right->data) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

template <typename T>
bool set<T>::contains(const_reference value) const {
  return nullptr != innerSearch(root_, value);
}

template <typename T>
typename set<T>::iterator set<T>::find(const_reference value) const {
  return iterator(innerSearch(root_, value));
}

template <typename T>
typename set<T>::Node* set<T>::innerSearch(Node* node, T value) const {
  if (node == nullptr || node->data == value) {
    return node;
  } else if (value < node->data) {
    return innerSearch(node->left, value);
  } else {
    return innerSearch(node->right, value);
  }
}

template <typename T>
bool set<T>::empty() const {
  return root_ == nullptr;
}

template <typename T>
void set<T>::clear() {
  clear(root_);
  len = 0;
}

template <typename T>
typename set<T>::size_type set<T>::size() {
  return len;
}

// multiply by two because w/o this dont pass the tests
template <typename T>
typename set<T>::size_type set<T>::max_size() {
  return MAX_MEMORY / sizeof(Node);
}

template <typename T>
void set<T>::clear(Node*& node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
  }
}

template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const_reference value) {
  typename set<T>::size_type lc = this->size();
  root_ = innerInsert(root_, value, nullptr);
  bool r = true;
  if (lc - this->size() == 0) r = false;
  Node* current = innerSearch(root_, value);

  return {iterator(current), r};
}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  Node* current = root_;
  while (current && current->left) {
    current = current->left;
  }
  return iterator(current);
}

template <typename T>
typename set<T>::const_iterator set<T>::begin() const {
  Node* current = root_;
  while (current && current->left) {
    current = current->left;
  }
  return const_iterator(current);
}

template <typename T>
typename set<T>::Node* set<T>::innerRemove(Node* node, T value) {
  if (node == nullptr) return node;
  if (value < node->data) {
    node->left = innerRemove(node->left, value);
    if (node->left) node->left->parent = node;
  } else if (value > node->data) {
    node->right = innerRemove(node->right, value);
    if (node->right) node->right->parent = node;
  } else {
    if ((node->left == nullptr) || (node->right == nullptr)) {
      Node* temp = node->left ? node->left : node->right;
      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
        node->parent = temp->parent;
      }
      delete temp;
      --len;
    } else {
      Node* temp = minValueNode(node->right);
      node->data = temp->data;
      node->right = innerRemove(node->right, temp->data);
      if (node->right) node->right->parent = node;
    }
  }
  if (node == nullptr) return node;
  updateHeight(node);
  int balance = balanceFactor(node);
  if (balance > 1 && balanceFactor(node->left) >= 0) {
    return rotateRight(node);
  }
  if (balance > 1 && balanceFactor(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && balanceFactor(node->right) <= 0) {
    return rotateLeft(node);
  }
  if (balance < -1 && balanceFactor(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

template <typename T>
typename set<T>::Node* set<T>::minValueNode(Node* node) {
  Node* current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

template <typename T>
void set<T>::erase(iterator pos) {
  root_ = innerRemove(root_, *pos);
}

template <typename T>
void set<T>::swap(set& other) {
  std::swap(root_, other.root_);
  std::swap(len, other.len);
}

template <typename T>
void set<T>::merge(set& other) {
  for (const auto& elem : other) {
    insert(elem);
  }
}

template <typename T>
template <typename... Args>
s21::vector<std::pair<typename s21::set<T>::iterator, bool>>
set<T>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> res;
  for (const auto& elem : {args...}) {
    res.push_back(insert(elem));
  }
  return res;
}

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_SET_TEMPLATE_S21_SET_TEMPLATE_H_
