#ifndef CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_

#include <iostream>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() noexcept;
  array(std::initializer_list<value_type> const &items);
  array(const array<T, N> &a);
  array(array<T, N> &&a) noexcept;
  ~array() = default;  // ???????
  array &operator=(const array &a) noexcept;
  array &operator=(array &&a) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  iterator data() noexcept;
  const_iterator data() const noexcept;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(array &other);
  void fill(const_reference value);

 private:
  value_type data_[N] = {};
  size_type size_ = N;
};
}  // namespace s21

#include "s21_array.tpp"
#endif  // CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_