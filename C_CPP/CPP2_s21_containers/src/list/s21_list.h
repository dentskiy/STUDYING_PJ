#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_S21_LIST_H_

#include <initializer_list>

namespace s21 {

template <typename T>
class list {
 public:
  class ListConstIterator;
  class ListIterator;

 private:
  struct Node {
    Node *next, *back;
    T arg;
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
    bool operator!=(ListIterator it) const { return node != it.node; };
    bool operator!=(ListConstIterator it) const { return node != it.node; };
    bool operator==(ListIterator it) const { return node == it.node; };
    bool operator==(ListConstIterator it) const { return node == it.node; };
  };

 public:
  class ListIterator : public BaseIterator<ListIterator> {
    friend class BaseIterator<ListIterator>;
    friend class BaseIterator<ListConstIterator>;
    friend class list;

   public:
    ListIterator(Node* other = nullptr) { this->node = other; };
    ~ListIterator(){};

    T& operator*() { return this->node->arg; }
  };

  class ListConstIterator : public BaseIterator<ListConstIterator> {
    friend class BaseIterator<ListIterator>;
    friend class BaseIterator<ListConstIterator>;
    friend class list;

   public:
    ListConstIterator(Node* const other = nullptr) { this->node = other; };
    ListConstIterator(const ListIterator& other) { this->node = other.node; };
    ListConstIterator(ListIterator&& other) {
      this->node = other.node;
      other.node = nullptr;
    };
    ~ListConstIterator(){};

    const T& operator*() { return this->node->arg; }
  };

 private:
  Node fake_;
  Node* start_;
  Node* finish_;

 public:
  // List Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // List Functions
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();

  list& operator=(list&& l);
  list& operator=(const list& l);

  // List Element access
  const_reference front() { return start_->arg; }
  const_reference back() { return finish_->back->arg; }

  // List Iterators
  iterator begin() { return iterator(start_); };
  iterator end() { return iterator(finish_); };
  const_iterator begin() const { return const_iterator(start_); }
  const_iterator end() const { return const_iterator(finish_); }

  // List Capacity
  bool empty() { return start_ == finish_; };
  size_type size();
  size_type max_size();

  // List Modifiers
  iterator insert(iterator pos, const_reference value);
  iterator erase(iterator pos);
  void push_back(const_reference val);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  void clear();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
};

};  // namespace s21
#include "internal_class.tpp"
#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_LIST_S21_LIST_H_