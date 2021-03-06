#ifndef DWARF_SHARED_QUEUE_H_
#define DWARF_SHARED_QUEUE_H_

#include <assert.h>

#include "dwarf.h"

namespace dwarf {

template <typename TItem>
class Queue {
  public:
    typedef TItem ItemType;
    Queue();
    Queue(I32 capacity);
    ~Queue();
    I32 capacity() const;
    I32 length() const;
    BOOL IsEmpty() const;
    void Push(TItem item);
    TItem Pop();
    TItem Peek();
    void Clear();

    class Iterator {
      public:
        Iterator(const Queue<TItem>& queue);
        ~Iterator();
        BOOL HasNext() const;
        TItem Next();

      private:
        I32 position_;
        const Queue<TItem>& queue_;
    };

    friend class Iterator;

  private:
    I32 capacity_;
    I32 first_;
    I32 last_;
    I32 length_;
    TItem* data_;
    void Initialize();
    void Cleanup();
    void Resize(I32 new_capacity);
};

template <typename TItem>
inline Queue<TItem>::Queue()
    : capacity_(4) {
  Initialize();
}

template <typename TItem>
inline Queue<TItem>::Queue(I32 capacity)
    : capacity_(capacity) {
  Initialize();
}

template <typename TItem>
inline Queue<TItem>::~Queue() {
  Cleanup();
}

template <typename TItem>
inline I32 Queue<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline I32 Queue<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline BOOL Queue<TItem>::IsEmpty() const {
  return length_ == 0;
}

template <typename TItem>
inline void Queue<TItem>::Push(TItem item) {
  if (length_ == capacity_) {
    I32 new_capacity = 2 * capacity_ + 1;
    Resize(new_capacity);
  }
  if (length_ == 0) {
    first_ = 0;
  }
  last_ = (last_ + 1) % capacity_;
  data_[last_] = item;
  length_++;
}

template <typename TItem>
inline TItem Queue<TItem>::Pop() {
  assert(length_ > 0 && "queue is empty");
  TItem item = data_[first_];
  first_ = (first_ + 1) % capacity_;
  length_--;
  if (length_ == 0) {
    first_ = -1;
    last_ = -1;
  }
  return item;
}

template <typename TItem>
inline TItem Queue<TItem>::Peek() {
  assert(length_ > 0 && "queue is empty");
  return data_[first_];
}

template <typename TItem>
inline void Queue<TItem>::Clear() {
  Cleanup();
  Initialize();
}

template <typename TItem>
inline void Queue<TItem>::Initialize() {
  first_ = -1;
  last_ = -1;
  length_ = 0;
  data_ = new TItem[capacity_];
}

template <typename TItem>
inline void Queue<TItem>::Cleanup() {
  delete[] data_;
}

template <typename TItem>
inline void Queue<TItem>::Resize(I32 new_capacity) {
  TItem* new_data = new TItem[new_capacity];
  for (I32 i = 0; i < length_; ++i) {
    new_data[i] = data_[((first_ + i) % capacity_)];
  }
  Cleanup();
  data_ = new_data;
  first_ = 0;
  last_ = length_ - 1;
  capacity_ = new_capacity;
}

template <typename TItem>
inline Queue<TItem>::Iterator::Iterator(const Queue<TItem>& queue)
    : position_(0),
      queue_(queue) {
}

template <typename TItem>
inline Queue<TItem>::Iterator::~Iterator() {
}

template <typename TItem>
inline BOOL Queue<TItem>::Iterator::HasNext() const {
  return position_ < queue_.length();
}

template <typename TItem>
inline TItem Queue<TItem>::Iterator::Next() {
  I32 index = (queue_.first_ + position_) % queue_.capacity_;
  position_++;
  return queue_.data_[index];
}

}

#endif