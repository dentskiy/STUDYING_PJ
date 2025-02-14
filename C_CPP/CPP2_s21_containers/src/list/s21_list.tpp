#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_S21_LIST_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_S21_LIST_TPP_

#include <iostream>
namespace s21 {

template <typename tmp>
list<tmp>::list() : fake_{}, start_{&fake_}, finish_{&fake_} {
  finish_->next = finish_;
  finish_->back = finish_;
}

template <typename tmp>
list<tmp>::list(size_type n) : list<tmp>::list() {
  value_type def{};
  for (size_type i = 0; i < n; i++) {
    push_back(def);
  }
}

template <typename tmp>
list<tmp>::list(std::initializer_list<value_type> const& items)
    : list<tmp>::list() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push_back(*it);
  }
}

template <typename tmp>
list<tmp>::list(const list<tmp>& l) : list<tmp>::list() {
  for (const_iterator it = l.begin(); it != l.end(); it++) {
    push_back(*it);
  }
}

template <typename tmp>
list<tmp>::list(list<tmp>&& l) : list() {
  *this = std::move(l);
}

template <typename tmp>
list<tmp>::~list() {
  clear();
}

template <typename tmp>
typename s21::list<tmp>& list<tmp>::operator=(list<tmp>&& l) {
  if (this != &l) {
    clear();
    if (!l.empty()) {
      fake_ = l.fake_;
      start_ = finish_->next;
      finish_->back->next = finish_;
      finish_->next->back = finish_;
      l.start_ = l.finish_;
      l.finish_->next = l.finish_;
      l.finish_->back = l.finish_;
    }
  }
  return *this;
}

template <typename tmp>
typename s21::list<tmp>& list<tmp>::operator=(const list& l) {
  if (this != &l) {
    clear();
    list<tmp> buf(l);
    *this = std::move(buf);
  }
  return *this;
}
// funcs

template <typename T>
typename s21::list<T>::ListIterator list<T>::insert(iterator pos,
                                                    const_reference value) {
  Node* tmp = new Node{pos.node, pos.node->back, value};
  tmp->back->next = tmp;
  pos.node->back = tmp;
  if (pos.node == start_) start_ = tmp;
  pos--;
  return pos;
}

template <typename T>
typename s21::list<T>::iterator list<T>::erase(iterator pos) {
  Node* tmp{pos.node->next};
  pos.node->next->back = pos.node->back;
  pos.node->back->next = pos.node->next;
  if (pos.node == start_) start_ = pos.node->next;
  delete pos.node;
  pos.node = tmp;
  return pos;
}

template <typename tmp>
void list<tmp>::push_back(const_reference val) {
  insert(end(), val);
}

template <typename T>
void list<T>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename T>
void list<T>::pop_back() {
  erase(--end());
}

template <typename T>
void list<T>::pop_front() {
  erase(begin());
}

template <typename T>
size_t list<T>::size() {
  size_t count = 0;
  for (const_iterator it = begin(); it != end(); it++) count++;
  return count;
}

template <typename T>
void list<T>::clear() {
  while (start_ != finish_) {
    pop_front();
  }
}

template <typename T>
void list<T>::swap(list<T>& other) {
  if (this != &other) {
    std::swap(fake_, other.fake_);
    if (other.empty()) finish_->next = finish_->back = finish_;
    if (empty()) other.finish_->next = other.finish_->back = other.finish_;
    finish_->next->back = finish_;
    finish_->back->next = finish_;
    start_ = finish_->next;
    other.finish_->next->back = other.finish_;
    other.finish_->back->next = other.finish_;
    other.start_ = other.finish_->next;
  }
}

template <typename T>
void list<T>::merge(list<T>& other) {
  if (this != &other) {
    for (iterator it = begin(); it != end() && !other.empty(); it++) {
      while (other.front() < *it) {
        insert(it, other.front());
        other.pop_front();
      }
    }
    splice(end(), other);
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list<T>& other) {
  if (other.empty()) return;
  if (this == &other) return;
  pos.node->back->next = other.start_;
  other.start_->back = pos.node->back;
  other.finish_->back->next = pos.node;
  pos.node->back = other.finish_->back;
  other.start_ = other.finish_;
  other.finish_->back = other.finish_;
  other.finish_->next = other.finish_;
  if (pos == begin()) start_ = finish_->next;
}

template <typename T>
void list<T>::reverse() {
  if (!empty()) {
    Node* tmp = nullptr;
    for (iterator it = begin(); it != end(); it--) {
      tmp = it.node->next;
      it.node->next = it.node->back;
      it.node->back = tmp;
    }
    tmp = finish_->next;
    finish_->next = finish_->back;
    finish_->back = tmp;
    start_ = finish_->next;
  }
}

template <typename T>
void list<T>::unique() {
  for (iterator iter = begin(); iter != end(); iter++) {
    iterator it(iter.node->next);
    while (*iter == *it && it != end()) it = erase(it);
  }
}

template <typename T>
void list<T>::sort() {
  value_type tmp{};
  for (iterator iter = begin(); iter != end(); iter++) {
    iterator min = iter;
    for (iterator it(iter.node->next); it != end(); it++)
      if (*min > *it) min = it;
    if (min != iter) {
      tmp = *min;
      *min = *iter;
      *iter = tmp;
    }
  }
}

template <typename T>
typename s21::list<T>::size_type list<T>::max_size() {
  return MAX_MEMORY / sizeof(Node);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator it{pos.node};

  for (auto arg : {args...}) {
    insert(it, arg);
  }
  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (auto arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (auto arg : {args...}) {
    push_front(arg);
  }
}

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_LIST_S21_LIST_TPP_