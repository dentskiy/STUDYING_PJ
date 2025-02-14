#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_

#include <initializer_list>
#include <iterator>

#include "../vector/s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  class MapConstIterator;
  class MapIterator;

  using value_type = std::pair<const Key, T>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using size_type = size_t;

 private:
  struct Node {
    bool less;
    Node* parent;
    Node* left;
    Node* right;
    value_type val;
  };

  template <class Iter>
  class BaseIterator {
   protected:
    Node* node;

   public:
    BaseIterator() : node(nullptr){};
    ~BaseIterator(){};

    Iter operator++();
    Iter operator--();
    Iter operator++(int);
    Iter operator--(int);
    bool operator==(iterator it);
    bool operator==(const_iterator it);
    bool operator!=(iterator it);
    bool operator!=(const_iterator it);

   protected:
    bool goLeft();
    bool goRight();
    bool goParent();
  };

 public:
  class MapIterator : public BaseIterator<MapIterator> {
    friend class map;
    friend class BaseIterator<MapIterator>;
    friend class BaseIterator<MapConstIterator>;

   public:
    MapIterator(Node* nd = nullptr) { this->node = nd; };
    ~MapIterator(){};

    reference operator*();
    value_type* operator->();
  };

  class MapConstIterator : public BaseIterator<MapConstIterator> {
    friend class map;
    friend class BaseIterator<MapIterator>;
    friend class BaseIterator<MapConstIterator>;

   public:
    MapConstIterator(Node* const nd) { this->node = nd; };
    MapConstIterator(const iterator& it) { this->node = it.node; };
    MapConstIterator(iterator&& it) {
      this->node = it.node;
      it.node = nullptr;
    };
    ~MapConstIterator(){};

    const_iterator& operator=(const iterator& it) const;
    const_reference operator*() const;
    const value_type* operator->() const;
  };

 private:
  size_type size_;
  Node fake_;
  Node*& top_;
  Node*& min_;
  Node* end_;

 public:
  // Map Member functions
  map();
  ~map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  map& operator=(map&& m);

  // Map Element access
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Map Iterators
  iterator begin() { return iterator(min_); };
  iterator end() { return iterator(end_); };
  const_iterator begin() const { return const_iterator(min_); };
  const_iterator end() const { return const_iterator(end_); };

  // Map Capacity
  bool empty();
  size_type size() { return size_; };
  size_type max_size() { return MAX_MEMORY / sizeof(Node); };

  // Map Modifiers
  void clear();
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  iterator erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  // Map Lookup
  bool contains(const Key& key);

 private:
  // Map Support
  iterator search(const Key& key);
  iterator cut_node(iterator pos);
  void set_node(iterator pos, iterator it);
};

};  // namespace s21

#include "map_iterator.tpp"
#include "map_support.tpp"
#include "s21_map.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_