#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_TPP_

#include <iostream>

namespace s21 {

// Map Member functions
template <typename Key, typename T>
map<Key, T>::map()
    : size_{},
      fake_{false, nullptr, nullptr, &fake_, {}},
      top_{fake_.left},
      min_{fake_.right},
      end_{&fake_} {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) : map() {
  for (auto it = items.begin(); it != items.end(); it++) insert(*it);
}

template <typename Key, typename T>
map<Key, T>::map(const map<Key, T>& m) : map() {
  for (const_iterator it = m.begin(); it != m.end(); it++) insert(*it);
}

template <typename Key, typename T>
map<Key, T>::map(map<Key, T>&& m) : map() {
  *this = std::move(m);
}

template <typename Key, typename T>
typename s21::map<Key, T>& map<Key, T>::operator=(map<Key, T>&& m) {
  if (this != &m) {
    clear();
    if (!m.empty()) {
      top_ = m.top_;
      top_->parent = &fake_;
      min_ = m.min_;
      m.top_ = nullptr;
      m.min_ = m.end_;
      size_ = m.size_;
      m.size_ = 0;
    }
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T>::~map() {
  clear();
}

// Map Element access
template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  if (empty()) throw std::out_of_range("Map is empty\n");
  iterator it = search(key);
  if (it->first != key) throw std::out_of_range("Value doesn't exist\n");
  return it->second;
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  return insert(key, {}).first->second;
}

// Map Capacity
template <typename Key, typename T>
bool map<Key, T>::empty() {
  return min_ == end_;
}

// Map Modifiers
template <typename Key, typename T>
void map<Key, T>::clear() {
  while (!empty()) {
    erase(begin());
  }
}

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  return insert({key, obj});
}

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  auto res = insert({key, obj});
  if (!res.second) res.first->second = obj;
  return res;
}

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  const Key& key = value.first;
  std::pair<iterator, bool> res{search(key), true};
  iterator& it = res.first;
  iterator elem;
  if (empty()) {
    top_ = new Node{true, min_, nullptr, nullptr, value};
    min_ = top_;
    it.goLeft();
    size_++;
  } else if (it->first != key) {
    elem.node = new Node{0, 0, 0, 0, value};
    set_node(it, elem);
    it = elem;
  } else {
    res.second = false;
  }
  return res;
}

template <typename Key, typename T>
typename s21::map<Key, T>::iterator map<Key, T>::erase(iterator pos) {
  iterator res = cut_node(pos);
  delete pos.node;
  return res;
}

template <typename Key, typename T>
void map<Key, T>::swap(map<Key, T>& other) {
  map buff;
  if (this != &other) {
    buff = std::move(other);
    other = std::move(*this);
    *this = std::move(buff);
  }
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  if (this == &other || other.empty()) return;
  if (empty()) {
    *this = std::move(other);
  } else {
    for (auto it = other.begin(); it != other.end(); it++) {
      auto pos = search(it->first);
      while (pos->first != it->first && it != other.end()) {
        auto buff = other.cut_node(it);
        set_node(pos, it);
        it = buff;
        pos = search(it->first);
      }
    }
  }
}

template <typename Key, typename T>
template <typename... Args>
s21::vector<std::pair<typename s21::map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> res;
  for (const auto& elem : {args...}) {
    res.push_back(insert(elem));
  }
  return res;
}

// Map Lookup
template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  if (empty()) return false;
  return search(key)->first == key;
}

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_TPP_