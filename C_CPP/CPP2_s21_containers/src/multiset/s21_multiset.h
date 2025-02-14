#ifndef CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_

#include <initializer_list>

#include "../set/s21_set.h"

namespace s21 {

template <typename T>
class multiset : public set<T> {
 public:
  using typename set<T>::key_type;
  using typename set<T>::value_type;
  using typename set<T>::reference;
  using typename set<T>::const_reference;
  using typename set<T>::iterator;
  using typename set<T>::const_iterator;
  using typename set<T>::size_type;
  using set<T>::set;

 public:
  std::pair<iterator, bool> insert(const T& value);

  void erase(iterator pos);

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& s);
  multiset(multiset&& s);
  multiset<T>& operator=(const multiset& s);
  multiset<T>& operator=(multiset&& s);

  void merge(multiset& other);

  size_type count(T value) {
    return this->innerSearch(this->root_, value)->amount;
  };

  typename set<T>::Node* innerInsert(typename set<T>::Node* node, T value,
                                     typename set<T>::Node* parent);
  void innerInsert(T value);
  typename set<T>::Node* findFirstGreaterEqual(typename set<T>::Node* root_,
                                               T value);
  typename set<T>::Node* findFirstGreater(typename set<T>::Node* root_,
                                          T value);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  std::pair<iterator, iterator> equal_range(const T& key);
  iterator lower_bound(const T& key);
  iterator upper_bound(const T& key);
};

}  // namespace s21

#include "template/s21_multiset_template.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_
