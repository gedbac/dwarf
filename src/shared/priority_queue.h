#ifndef DWARF_SHARED_PRIORITY_QUEUE_H_
#define DWARF_SHARED_PRIORITY_QUEUE_H_

namespace dwarf {
namespace shared {

#include <string.h>
#include <assert.h>
#include <math.h>

#include "comparer.h"

template <typename TItem>
class PriorityQueue {
  public:
    typedef TItem ItemType;
    PriorityQueue(const Comparer<TItem>& comparer = Comparer<TItem>());
	  PriorityQueue(int capacity, const Comparer<TItem>& comparer = Comparer<TItem>());
	  ~PriorityQueue();
	  int capacity() const;
    int length() const;
    bool IsEmpty() const;
    void Clear();
    void Push(TItem item);
    TItem Pop();
    TItem Peek();

    class Iterator {
      public:
        Iterator(const PriorityQueue<TItem>& queue);
        ~Iterator();
        bool HasNext() const;
        TItem Next();

      private:
        int position_;
        const PriorityQueue<TItem>& queue_;
    };

    friend class Iterator;

  private:
    int capacity_;
    int length_;
    TItem* heap_;
    const Comparer<TItem>& comparer_;
    void Initialize(int capacity);
    void Cleanup(TItem* heap);
    void Resize(int new_capacity);
    void Swap(TItem& a, TItem& b);
    int Compare(TItem& a, TItem& b) const;
    void ShiftUp(int index);
    void ShiftDown(int index);
};

template <typename TItem>
inline PriorityQueue<TItem>::PriorityQueue(const Comparer<TItem>& comparer)
    : capacity_(4),
      comparer_(comparer) {
  Initialize(capacity_);
}

template <typename TItem>
inline PriorityQueue<TItem>::PriorityQueue(int capacity, const Comparer<TItem>& comparer)
    : capacity_(capacity),
      comparer_(comparer) {
  Initialize(capacity_);
}

template <typename TItem>
inline PriorityQueue<TItem>::~PriorityQueue() {
  Cleanup(heap_);
}

template <typename TItem>
inline int PriorityQueue<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline int PriorityQueue<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline bool PriorityQueue<TItem>::IsEmpty() const {
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
    int new_capacity = 2 * capacity_ + 1;
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
inline void PriorityQueue<TItem>::Initialize(int capacity) {
  length_ = 0;
  heap_ = new TItem[capacity];
}

template <typename TItem>
inline void PriorityQueue<TItem>::Cleanup(TItem* heap) {
  delete[] heap;
}

template <typename TItem>
inline void PriorityQueue<TItem>::Resize(int new_capacity) {
  TItem* new_heap = new TItem[new_capacity];
  memcpy(new_heap, heap_, capacity_ * sizeof(TItem));
  Cleanup(heap_);
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
inline int PriorityQueue<TItem>::Compare(TItem& a, TItem& b) const {
  return comparer_.Compare(a, b);
}

template <typename TItem>
inline void PriorityQueue<TItem>::ShiftUp(int index) {
  int parent = floor((index - 1) / 2);
  if (index > 0 && Compare(heap_[index], heap_[parent]) == 1) {
    Swap(heap_[index], heap_[parent]);
    ShiftUp(parent);
  }
}

template <typename TItem>
inline void PriorityQueue<TItem>::ShiftDown(int index) {
  if (index < length_) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
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
inline bool PriorityQueue<TItem>::Iterator::HasNext() const {
  return position_ < queue_.length();
}

template <typename TItem>
inline TItem PriorityQueue<TItem>::Iterator::Next() {
  return queue_.heap_[position_++];
}

}
}

#endif