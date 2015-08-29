#ifndef DWARF_SHARED_PRIORITY_QUEUE_H_
#define DWARF_SHARED_PRIORITY_QUEUE_H_

#include "dwarf.h"
#include "comparer.h"

namespace dwarf {

#include <string.h>
#include <assert.h>
#include <math.h>

template <typename TItem>
class PriorityQueue {
  public:
    typedef TItem ItemType;
    PriorityQueue(const Comparer<TItem>& comparer = Comparer<TItem>());
	  PriorityQueue(I32 capacity, const Comparer<TItem>& comparer = Comparer<TItem>());
	  ~PriorityQueue();
	  I32 capacity() const;
    I32 length() const;
    BOOL IsEmpty() const;
    void Clear();
    void Push(TItem item);
    TItem Pop();
    TItem Peek();

    class Iterator {
      public:
        Iterator(const PriorityQueue<TItem>& queue);
        ~Iterator();
        BOOL HasNext() const;
        TItem Next();

      private:
        I32 position_;
        const PriorityQueue<TItem>& queue_;
    };

    friend class Iterator;

  private:
    I32 capacity_;
    I32 length_;
    TItem* heap_;
    const Comparer<TItem>& comparer_;
    void Initialize();
    void Cleanup();
    void Resize(I32 new_capacity);
    void Swap(TItem& a, TItem& b);
    I32 Compare(TItem& a, TItem& b) const;
    void ShiftUp(I32 index);
    void ShiftDown(I32 index);
};

template <typename TItem>
inline PriorityQueue<TItem>::PriorityQueue(const Comparer<TItem>& comparer)
    : capacity_(4),
      comparer_(comparer) {
  Initialize();
}

template <typename TItem>
inline PriorityQueue<TItem>::PriorityQueue(I32 capacity, const Comparer<TItem>& comparer)
    : capacity_(capacity),
      comparer_(comparer) {
  Initialize();
}

template <typename TItem>
inline PriorityQueue<TItem>::~PriorityQueue() {
  Cleanup();
}

template <typename TItem>
inline I32 PriorityQueue<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline I32 PriorityQueue<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline BOOL PriorityQueue<TItem>::IsEmpty() const {
  return length_ == 0;
}

template <typename TItem>
inline void PriorityQueue<TItem>::Clear() {
  Cleanup(heap_);
  Initialize(capacity_);
}

template <typename TItem>
inline void PriorityQueue<TItem>::Push(TItem item) {
  if (length_ == capacity_) {
    I32 new_capacity = 2 * capacity_ + 1;
    Resize(new_capacity);
  }
  heap_[length_++] = item;
  if (length_ > 1) {
    ShiftUp(length_ - 1);
  }
}

template <typename TItem>
inline TItem PriorityQueue<TItem>::Pop() {
  assert(length_ > 0 && "queue is empty");
  TItem item = heap_[0];
  length_--;
  if (length_ > 1) {
    Swap(heap_[0], heap_[length_]);
    ShiftDown(0);
  }
  return item;
}

template <typename TItem>
inline TItem PriorityQueue<TItem>::Peek() {
  assert(length_ > 0 && "queue is empty");
  return heap_[0];
}

template <typename TItem>
inline void PriorityQueue<TItem>::Initialize() {
  length_ = 0;
  heap_ = new TItem[capacity_];
}

template <typename TItem>
inline void PriorityQueue<TItem>::Cleanup() {
  delete[] heap_;
}

template <typename TItem>
inline void PriorityQueue<TItem>::Resize(I32 new_capacity) {
  TItem* new_heap = new TItem[new_capacity];
  memcpy(new_heap, heap_, capacity_ * sizeof(TItem));
  Cleanup();
  heap_ = new_heap;
  capacity_ = new_capacity;
}

template <typename TItem>
inline void PriorityQueue<TItem>::Swap(TItem &a, TItem &b) {
  TItem temp = a;
  a = b;
  b = temp;
}

template <typename TItem>
inline I32 PriorityQueue<TItem>::Compare(TItem& a, TItem& b) const {
  return comparer_.Compare(a, b);
}

template <typename TItem>
inline void PriorityQueue<TItem>::ShiftUp(I32 index) {
  I32 parent = floor((index - 1) / 2);
  if (index > 0 && Compare(heap_[index], heap_[parent]) == 1) {
    Swap(heap_[index], heap_[parent]);
    ShiftUp(parent);
  }
}

template <typename TItem>
inline void PriorityQueue<TItem>::ShiftDown(I32 index) {
  if (index < length_) {
    I32 left = 2 * index + 1;
    I32 right = 2 * index + 2;
    I32 largest = index;
    if (left < length_ && Compare(heap_[left], heap_[largest]) == 1) {
      largest = left;
    }
    if (right < length_ && Compare(heap_[right], heap_[largest]) == 1) {
      largest = right;
    }
    if (largest != index) {
      Swap(heap_[index], heap_[largest]);
      ShiftDown(largest);
    }
  }
}

template <typename TItem>
inline PriorityQueue<TItem>::Iterator::Iterator(const PriorityQueue<TItem>& queue)
    : position_(0),
      queue_(queue) {
}

template <typename TItem>
inline PriorityQueue<TItem>::Iterator::~Iterator() {
}

template <typename TItem>
inline BOOL PriorityQueue<TItem>::Iterator::HasNext() const {
  return position_ < queue_.length();
}

template <typename TItem>
inline TItem PriorityQueue<TItem>::Iterator::Next() {
  return queue_.heap_[position_++];
}

}

#endif