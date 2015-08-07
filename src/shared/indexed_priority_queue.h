#ifndef DWARF_SHARED_INDEXED_PRIORITY_QUEUE_H_
#define DWARF_SHARED_INDEXED_PRIORITY_QUEUE_H_

namespace dwarf {
namespace shared {

#include <string.h>
#include <assert.h>
#include <math.h>

#include "comparer.h"

template <typename TItem>
class IndexedPriorityQueue {
  public:
    typedef TItem ItemType;
	  IndexedPriorityQueue(const Comparer<TItem>& comparer = Comparer<TItem>());
	  IndexedPriorityQueue(int capacity, const Comparer<TItem>& comparer = Comparer<TItem>());
	  ~IndexedPriorityQueue();
	  int capacity() const;
    int length() const;
    bool IsEmpty() const;
    void Clear();
    void Push(int index, TItem item);
    TItem Pop();
    TItem Peek();
    void Change(int index);
    TItem& operator[] (int index) const;

    class Iterator {
      public:
        Iterator(const IndexedPriorityQueue<TItem>& queue);
        ~Iterator();
        bool HasNext() const;
        TItem Next();

      private:
        int position_;
        const IndexedPriorityQueue<TItem>& queue_;
    };

    friend class Iterator;

  private:
    int capacity_;
    int length_;
    TItem* data_;
    int* heap_;
    int* inverse_heap_;
    const Comparer<TItem>& comparer_;
    void Initialize(int capacity);
    void Cleanup(TItem* data, int* heap, int* inverse_heap);
    void Resize(int new_capacity);
    void Swap(int a, int b);
    int Compare(TItem& a, TItem& b) const;
    void ShiftUp(int index);
    void ShiftDown(int index);
};

template <typename TItem>
inline IndexedPriorityQueue<TItem>::IndexedPriorityQueue(const Comparer<TItem>& comparer)
    : capacity_(4),
      comparer_(comparer) {
  Initialize(capacity_);
}

template <typename TItem>
inline IndexedPriorityQueue<TItem>::IndexedPriorityQueue(int capacity, const Comparer<TItem>& comparer)
    : capacity_(capacity),
      comparer_(comparer) {
  Initialize(capacity_);
}

template <typename TItem>
inline IndexedPriorityQueue<TItem>::~IndexedPriorityQueue() {
  Cleanup(data_, heap_, inverse_heap_);
}

template <typename TItem>
inline int IndexedPriorityQueue<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline int IndexedPriorityQueue<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline bool IndexedPriorityQueue<TItem>::IsEmpty() const {
  return length_ == 0;
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Clear() {
  Cleanup(data_, heap_, inverse_heap_);
  Initialize(capacity_);
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Push(int index, TItem item) {
  if (length_ == capacity_) {
    int new_capacity = 2 * capacity_ + 1;
    Resize(new_capacity);
  }
  assert(index >= 0 && index <= length_ && "index out of range");
  data_[index] = item;
  heap_[length_] = index;
  inverse_heap_[index] = length_;
  length_++;
  if (length_ > 1) {
    ShiftUp(length_ - 1);
  }
}

template <typename TItem>
inline TItem IndexedPriorityQueue<TItem>::Pop() {
  assert(length_ > 0 && "queue is empty");
  TItem item = data_[heap_[0]];
  length_--;
  if (length_ > 1) {
    Swap(0, length_);
    ShiftDown(0);
  }
  return item;
}

template <typename TItem>
inline TItem IndexedPriorityQueue<TItem>::Peek() {
  assert(length_ > 0 && "queue is empty");
  return data_[heap_[0]];
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Change(int index) {
  assert(index >= 0 && index < length_ && "index out of range");
  ShiftUp(inverse_heap_[index]);
  ShiftDown(inverse_heap_[index]);
}

template <typename TItem>
inline TItem& IndexedPriorityQueue<TItem>::operator[] (int index) const {
  assert(index >= 0 && index < length_ && "index out of range");
  return heap_[inverse_heap_[index]];
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Initialize(int capacity) {
  length_ = 0;
  data_ = new TItem[capacity];
  heap_ = new int[capacity];
  inverse_heap_ = new int[capacity];
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Cleanup(TItem* data, int* heap, int* inverse_heap) {
  delete[] data;
  delete[] heap;
  delete[] inverse_heap;
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Resize(int new_capacity) {
  TItem* new_data = new TItem[new_capacity];
  memcpy(new_data, data_, capacity_ * sizeof(TItem));
  delete[] data_;
  data_ = new_data;
  int* new_heap = new int[new_capacity];
  memcpy(new_heap, heap_, capacity_ * sizeof(int));
  delete[] heap_;
  heap_ = new_heap;
  int* new_inverse_heap = new int[new_capacity];
  memcpy(new_inverse_heap, inverse_heap_, capacity_ * sizeof(int));
  delete[] inverse_heap_;
  inverse_heap_ = new_inverse_heap;
  capacity_ = new_capacity;
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::Swap(int a, int  b) {
  int temp = heap_[a];
  heap_[a] = heap_[b];
  heap_[b] = temp;
  inverse_heap_[heap_[a]] = a;
  inverse_heap_[heap_[b]] = b;
}

template <typename TItem>
inline int IndexedPriorityQueue<TItem>::Compare(TItem& a, TItem& b) const {
  return comparer_.Compare(a, b);
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::ShiftUp(int index) {
  int parent = floor((index - 1) / 2);
  if (index > 0 && Compare(data_[heap_[index]], data_[heap_[parent]]) == 1) {
    Swap(index, parent);
    ShiftUp(parent);
  }
}

template <typename TItem>
inline void IndexedPriorityQueue<TItem>::ShiftDown(int index) {
  if (index < length_) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
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
inline bool IndexedPriorityQueue<TItem>::Iterator::HasNext() const {
  return position_ < queue_.length();
}

template <typename TItem>
inline TItem IndexedPriorityQueue<TItem>::Iterator::Next() {
  return queue_.data_[queue_.heap_[position_++]];
}

}
}

#endif