#ifndef DWARF_SHARED_QUEUE_H_
#define DWARF_SHARED_QUEUE_H_

#include <assert.h>

namespace dwarf {
namespace shared {

template <typename TItem>
class Queue {
  public:
    typedef TItem ItemType;
    Queue();
    Queue(int capacity);
    ~Queue();
    int capacity() const;
    int length() const;
    bool IsEmpty() const;
    void Push(TItem item);
    TItem Pop();
    TItem Peek();
    void Clear();

    class Iterator {
      public:
        Iterator(const Queue<TItem>& queue);
        ~Iterator();
        bool HasNext() const;
        TItem Next();

      private:
        int position_;
        const Queue<TItem>& queue_;
    };

    friend class Iterator;

  private:
    int capacity_;
    int first_;
    int last_;
    int length_;
    TItem* data_;
    void Initialize(int capacity);
    void Cleanup(TItem* data);
    void Resize(int new_capacity);
};

template <typename TItem>
inline Queue<TItem>::Queue()
    : capacity_(4) {
  Initialize(capacity_);
}

template <typename TItem>
inline Queue<TItem>::Queue(int capacity)
    : capacity_(capacity) {
  Initialize(capacity_);
}

template <typename TItem>
inline Queue<TItem>::~Queue() {
  Cleanup(data_);
}

template <typename TItem>
inline int Queue<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline int Queue<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline bool Queue<TItem>::IsEmpty() const {
  return length_ == 0;
}

template <typename TItem>
inline void Queue<TItem>::Push(TItem item) {
  if (length_ == capacity_) {
    int new_capacity = 2 * capacity_ + 1;
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
  Cleanup(data_);
  Initialize(capacity_);
}

template <typename TItem>
inline void Queue<TItem>::Initialize(int capacity) {
  first_ = -1;
  last_ = -1;
  length_ = 0;
  data_ = new TItem[capacity];
}

template <typename TItem>
inline void Queue<TItem>::Cleanup(TItem* data) {
  delete[] data;
}

template <typename TItem>
inline void Queue<TItem>::Resize(int new_capacity) {
  TItem* new_data = new TItem[new_capacity];
  for (int i = 0; i < length_; ++i) {
    new_data[i] = data_[((first_ + i) % capacity_)];
  }
  Cleanup(data_);
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
inline bool Queue<TItem>::Iterator::HasNext() const {
  return position_ < queue_.length();
}

template <typename TItem>
inline TItem Queue<TItem>::Iterator::Next() {
  int index = (queue_.first_ + position_) % queue_.capacity_;
  position_++;
  return queue_.data_[index];
}

}
}

#endif