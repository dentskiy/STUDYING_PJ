#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_SUPPORT_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_SUPPORT_TPP_

namespace s21 {
template <typename Key, typename T>
typename s21::map<Key, T>::iterator map<Key, T>::search(const Key& key) {
  if (empty()) return end();
  iterator it(top_);
  for (bool flag = true; it->first != key && flag;) {
    while (it->first < key && flag) flag = it.goRight();
    while (it->first > key && flag) flag = it.goLeft();
  }
  return it;
}

template <typename Key, typename T>
typename s21::map<Key, T>::iterator map<Key, T>::cut_node(iterator pos) {
  iterator top = pos, left = pos, right = pos, res = pos;
  res++;
  top.goParent();
  left.goLeft();
  right.goRight();
  if (pos == left && pos == right) {
    (pos.node->less ? top.node->left : top.node->right) = nullptr;
  } else if (pos != right) {
    (pos.node->less ? top.node->left : top.node->right) = right.node;
    right.node->parent = top.node;
    right.node->less = pos.node->less;
  } else {
    (pos.node->less ? top.node->left : top.node->right) = left.node;
    left.node->parent = top.node;
    left.node->less = pos.node->less;
  }
  if (pos != left && pos != right) {
    while (right.goLeft())
      ;
    right.node->left = left.node;
    left.node->parent = right.node;
  }
  if (pos == begin()) min_ = res.node;
  pos.node->left = pos.node->right = pos.node->parent = nullptr;
  size_--;
  return res;
}

template <typename Key, typename T>
void map<Key, T>::set_node(iterator pos, iterator it) {
  it.node->parent = pos.node;
  it.node->less = pos->first > it->first;
  (it.node->less ? pos.node->left : pos.node->right) = it.node;
  if (min_->left) min_ = min_->left;
  size_++;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_SUPPORT_TPP_