#ifndef CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_TPP_

namespace s21 {

// default constructor
template <typename T>
vector<T>::vector() noexcept : data_{nullptr}, size_{}, capacity_{} {}

// Parameterized constructor
template <typename T>
vector<T>::vector(size_type n)
    : data_{new value_type[n]{}}, size_{n}, capacity_{n} {}

// Initializer list constructor
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

// Copy constructor
template <typename T>
vector<T>::vector(const vector<T> &v) : vector<T>(v.size_) {
  std::copy(v.cbegin(), v.cend(), data_);
}

// Move constructor
template <typename T>
vector<T>::vector(vector<T> &&v) noexcept
    : data_{v.data_}, size_{v.size_}, capacity_{v.capacity_} {
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
}

// Destructor
template <typename T>
vector<T>::~vector() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

// (operator =)
template <typename T>
vector<T> &vector<T>::operator=(const vector<T> &v) noexcept {
  if (this != &v) {
    vector copy{v};
    *this = std::move(copy);
  }
  return *this;
}

// (operator =) overload
template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
  if (this != &v) {
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
    std::swap(data_, v.data_);
    std::swap(size_, v.size_);
    std::swap(capacity_, v.capacity_);
  }

  return *this;
}

// Methods
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (this->empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (this->empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[size_ - 1];
}

template <typename T>
inline typename vector<T>::iterator vector<T>::data() noexcept {
  return &data_[0];
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::data() const noexcept {
  return &data_[0];
}

template <typename T>
inline typename vector<T>::iterator vector<T>::begin() {
  return &data_[0];
}

template <typename T>
inline typename vector<T>::iterator vector<T>::end() {
  return &data_[size_];
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::cbegin() const {
  return &data_[0];
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::cend() const {
  return &data_[size_];
}

template <typename T>
inline bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

// чё за нах?
template <typename T>
inline typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;

  // return (~(size_t)0 >> 1) / sizeof(value_type);
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= capacity_)
    return;
  else if (size > max_size()) {
    throw std::length_error("Size is larger than maximum of capacity");
  }
  iterator new_data = new value_type[size];
  std::copy(begin(), end(), new_data);
  delete[] data_;
  capacity_ = size;
  data_ = new_data;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    iterator new_data = new value_type[size_];
    std::copy(begin(), end(), new_data);
    delete[] data_;
    capacity_ = size_;
    data_ = new_data;
  }
}

// vector modifier
template <typename T>
void vector<T>::clear() noexcept {
  for (size_t i = 0; i < size(); i++) {
    data_[i] = 0;
  }
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type pos_num = pos - begin();
  if (size_ == capacity_) reserve(capacity_ ? capacity_ * 2 : 1);
  iterator new_pos = begin() + pos_num;

  push_back(value);

  std::rotate(new_pos, end() - 1, end());

  return new_pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos < begin() || pos > end()) return;

  std::move(pos + 1, end(), pos);
  pop_back();
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) reserve(capacity_ ? capacity_ * 2 : 1);
  data_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (!size_) throw std::out_of_range("Vector is empty");
  size_--;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> tmp{args...};

  size_type pos_num = pos - begin();
  iterator new_pos = begin() + pos_num;

  for (size_type i = 0; i < tmp.size(); i++) {
    new_pos = insert(new_pos, tmp[i]);
    new_pos++;
  }

  return new_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  vector<value_type> tmp{args...};

  for (size_type i = 0; i < tmp.size(); i++) {
    push_back(tmp[i]);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_TPP_