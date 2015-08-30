#ifndef DWARF_SHARED_INDEXED_PRIORITY_QUEUE_H_
#define DWARF_SHARED_INDEXED_PRIORITY_QUEUE_H_

#include <string.h>
#include <assert.h>
#include <math.h>

#include "dwarf.h"
#include "shared/comparer.h"

namespace dwarf {

template <typename TItem>
class IndexedPriorityQueue {
  public:
    typedef TItem ItemType;
	  IndexedPriorityQueue(const Comparer<TItem>& comparer = Comparer<TItem>());
	  IndexedPriorityQueue(I32 capacity, const Comparer<TItem>& comparer = Comparer<TItem>());
    ~IndexedPriorityQueue();
	  I32 capacity() const;
    I32 length() const;
    BOOL IsEmpty() const;
    void Clear();
    void Push(I32 index, TItem item);
    I32 Pop();
    I32 Peek();
    void Change(I32 index, TItem item);
    TItem& operator[] (I32 index) const;

    class Iterator {
      public:
        Iterator(const IndexedPriorityQueue<TItem>& queue);
        ~Iterator();
        BOOL HasNext() const;
        I32 Next();

      private:
        I32 position_;
        const IndexedPriorityQueue<TItem>& queue_;
    };

    friend class Iterator;

  private:
    I32 capacity_;
    I32 length_;
    TItem* data_;
    I32* heap_;
    I32* inverse_heap_;
    const Comparer<TItem>& comparer_;
    void Initialize();
    void Cleanup();
    void Resize(I32 new_capacity);
    void Swap(I32 a, I32 b);
    I32 Compare(TItem& a, TItem& b) const;
    void ShiftUp(I32 index);
    void ShiftDown(I32 index);
};

template <typename TItem>
inline IndexedPriorityQueue<TItem>::IndexedPriorityQueue(const Comparer<TItem>& comparer)
    : capacity_(4),
      comparer_(comparer) {
  Initialize();
}

template <typename TItem>
inline IndexedPriorityQueue<TItem>::IndexedPriorityQueue(I32 capacity, const Comparer<TItem>& comparer)
    : capacity_(capacity),
      comparer_(comparer) {
  Initialize();
}

template <typename TItem>
inline IndexedPriorityQueue<TItem>::~IndexedPriorityQueue() {
  Cleanup();
}

template <typename TItem>
inline I32 IndexedPriorityQueue<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline I32 IndexedPriorityQueue<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline BOOL IndexedPriorityQueue<TItem>::IsEmpty() const {
  return length_ == 0;
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Clear() {
  Cleanup();
  Initialize();
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Push(I32 index, TItem item) {
  I32 new_capacity = 0;
  if (length_ == capacity_) {
    new_capacity = 2 * capacity_ + 1;
    Resize(new_capacity);
  }
  if (index >= capacity_) {
    new_capacity = index + 1;
    Resize(new_capacity);
  }
  data_[index] = item;
  heap_[length_] = index;
  inverse_heap_[index] = length_;
  length_++;
  if (length_ > 1) {
    ShiftUp(length_ - 1);
  }
}

template <typename TItem>
inline I32 IndexedPriorityQueue<TItem>::Pop() {
  assert(length_ > 0 && "queue is empty");
  I32 index = heap_[0];
  length_--;
  if (length_ > 0) {
    Swap(0, length_);
    ShiftDown(0);
  }
  return index;
}

template <typename TItem>
inline I32 IndexedPriorityQueue<TItem>::Peek() {
  assert(length_ > 0 && "queue is empty");
  return heap_[0];
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Change(I32 index, TItem item) {
  assert(index >= 0 && index < capacity_ && "index out of range");
  data_[index] = item;
  ShiftUp(inverse_heap_[index]);
  ShiftDown(inverse_heap_[index]);
}

template <typename TItem>
inline TItem& IndexedPriorityQueue<TItem>::operator[] (I32 index) const {
  assert(index >= 0 && index < length_ && "index out of range");
  return heap_[inverse_heap_[index]];
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Initialize() {
  length_ = 0;
  data_ = new TItem[capacity_];
  heap_ = new I32[capacity_];
  inverse_heap_ = new I32[capacity_];
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Cleanup() {
  delete[] data_;
  delete[] heap_;
  delete[] inverse_heap_;
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Resize(I32 new_capacity) {
  TItem* new_data = new TItem[new_capacity];
  memcpy(new_data, data_, capacity_ * sizeof(TItem));
  delete[] data_;
  data_ = new_data;
  I32* new_heap = new I32[new_capacity];
  memcpy(new_heap, heap_, capacity_ * sizeof(I32));
  delete[] heap_;
  heap_ = new_heap;
  I32* new_inverse_heap = new I32[new_capacity];
  memcpy(new_inverse_heap, inverse_heap_, capacity_ * sizeof(I32));
  delete[] inverse_heap_;
  inverse_heap_ = new_inverse_heap;
  capacity_ = new_capacity;
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Swap(I32 a, I32  b) {
  I32 temp = heap_[a];
  heap_[a] = heap_[b];
  heap_[b] = temp;
  inverse_heap_[heap_[a]] = a;
  inverse_heap_[heap_[b]] = b;
}

template <typename TItem>
inline I32 IndexedPriorityQueue<TItem>::Compare(TItem& a, TItem& b) const {
  return comparer_.Compare(a, b);
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::ShiftUp(I32 index) {
  I32 parent = floor((index - 1) / 2);
  if (index > 0 && Compare(data_[heap_[index]], data_[heap_[parent]]) == 1) {
    Swap(index, parent);
    ShiftUp(parent);
  }
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::ShiftDown(I32 index) {
  if (index < length_) {
    I32 left = 2 * index + 1;
    I32 right = 2 * index + 2;
    I32 largest = index;
    if (left < length_ && Compare(data_[heap_[left]], data_[heap_[largest]]) == 1) {
      largest = left;
    }
    if (right < length_ && Compare(data_[heap_[right]], data_[heap_[largest]]) == 1) {
      largest = right;
    }
    if (largest != index) {
      Swap(index, largest);
      ShiftDown(largest);
    }
  }
}

template <typename TItem>
inline IndexedPriorityQueue<TItem>::Iterator::Iterator(const IndexedPriorityQueue<TItem>& queue)
    : position_(0),
      queue_(queue) {
}

template <typename TItem>
inline IndexedPriorityQueue<TItem>::Iterator::~Iterator() {
}

template <typename TItem>
inline BOOL IndexedPriorityQueue<TItem>::Iterator::HasNext() const {
  return position_ < queue_.length();
}

template <typename TItem>
inline I32 IndexedPriorityQueue<TItem>::Iterator::Next() {
  return queue_.heap_[position_++];
}

}

#endif