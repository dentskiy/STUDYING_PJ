#ifndef CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_TPP_
#include "s21_array.h"

namespace s21 {

// default constructor
template <typename T, std::size_t N>
array<T, N>::array() noexcept : size_(N) {}

// Initializer list constructor
template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  std::copy(items.begin(), items.end(), data_);
}

// Copy constructor
template <typename T, std::size_t N>
array<T, N>::array(const array<T, N> &a) {
  std::copy(a.data_, a.data_ + N, data_);
}

// Move constructor
template <typename T, std::size_t N>
array<T, N>::array(array<T, N> &&a) noexcept {
  std::move(a.data_, a.data_ + N, data_);
}

// (operator =)
template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array<T, N> &a) noexcept {
  if (this != &a) {
    array<T, N> copy(a);
    *this = std::move(copy);
  }
  return *this;
}

// (operator =) overload
template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&a) noexcept {
  if (this != &a) {
    std::move(a.data_, a.data_ + N, data_);
  }
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

// operator []
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

// front
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return data_[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

// iterator data() noexcept;
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return data_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const {
  return data_ + N;
}

// empty()
template <typename T, std::size_t N>
inline bool array<T, N>::empty() const {
  return size_ == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return size_;
}

// swap
template <typename T, std::size_t N>
void array<T, N>::swap(array<T, N> &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
}

// fill
template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(data_, data_ + N, value);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_TPP_