#ifndef DWARF_SHARED_STACK_H_
#define DWARF_SHARED_STACK_H_

#include <string.h>
#include <assert.h>

namespace dwarf {

template <typename TItem>
class Stack {
  public:
    typedef TItem ItemType;
    Stack();
    Stack(int capacity);
    ~Stack();
    int capacity() const;
    int length() const;
    bool IsEmpty() const;
    void Push(TItem item);
    TItem Pop();
    TItem Peek();
    void Clear();

    class Iterator {
      public:
        Iterator(const Stack<TItem>& stack);
        ~Iterator();
        bool HasNext() const;
        TItem Next();

      private:
        int position_;
        const Stack<TItem>& stack_;
    };

    friend class Iterator;

  private:
    int capacity_;
    int length_;
    TItem* data_;
    void Initialize();
    void Cleanup();
    void Resize(int new_capacity);
};

template <typename TItem>
inline Stack<TItem>::Stack()
    : capacity_(4) {
  Initialize();
}

template <typename TItem>
inline Stack<TItem>::Stack(int capacity)
    : capacity_(capacity) {
  Initialize();
}

template <typename TItem>
inline Stack<TItem>::~Stack() {
  Cleanup();
}

template <typename TItem>
inline int Stack<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline int Stack<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline bool Stack<TItem>::IsEmpty() const {
  return length_ == 0;
}

template <typename TItem>
inline void Stack<TItem>::Push(TItem item) {
  if (length_ >= capacity_) {
    int new_capacity = 2 * capacity_ + 1;
    Resize(new_capacity);
  }
  data_[length_++] = item;
}

template <typename TItem>
inline TItem Stack<TItem>::Pop() {
  assert(length_ > 0 && "stack is empty");
  return data_[--length_];
}

template <typename TItem>
inline TItem Stack<TItem>::Peek() {
  assert(length_ > 0 && "stack is empty");
  return data_[length_ - 1];
}

template <typename TItem>
inline void Stack<TItem>::Clear() {
  Cleanup();
  Initialize();
}

template <typename TItem>
inline void Stack<TItem>::Initialize() {
  length_ = 0;
  data_ = new TItem[capacity_];
}

template <typename TItem>
inline void Stack<TItem>::Cleanup() {
  delete[] data_;
}

template <typename TItem>
inline void Stack<TItem>::Resize(int new_capacity) {
  TItem* new_data = new TItem[new_capacity];
  memcpy(new_data, data_, capacity_ * sizeof(TItem));
  Cleanup();
  data_ = new_data;
  capacity_ = new_capacity;
}

template <typename TItem>
inline Stack<TItem>::Iterator::Iterator(const Stack<TItem>& stack)
    : position_(stack.length() - 1),
      stack_(stack) {
}

template <typename TItem>
inline Stack<TItem>::Iterator::~Iterator() {
}

template <typename TItem>
inline bool Stack<TItem>::Iterator::HasNext() const {
  return position_ >= 0;
}

template <typename TItem>
inline TItem Stack<TItem>::Iterator::Next() {
  return stack_.data_[position_--];
}

}

#endif