#ifndef DWARF_SHARED_LIST_H_
#define DWARF_SHARED_LIST_H_

#include <string.h>
#include <assert.h>

#include "dwarf.h"

namespace dwarf {

template <typename TItem>
class List {
  public:
    typedef TItem ItemType;
    List();
    List(I32 capacity);
    ~List();
    I32 capacity() const;
    I32 length() const;
    BOOL IsEmpty() const;
    TItem Get(I32 index) const;
    void Set(I32 index, TItem item);
    void Add(TItem item);
    BOOL Contains(TItem item) const;
    I32 IndexOf(TItem item) const;
    BOOL Remove(TItem item);
    void Insert(I32 index, TItem item);
    void Clear();
    TItem& operator[] (I32 index) const;

    class Iterator {
      public:
        Iterator(const List<TItem>& list);
        ~Iterator();
        BOOL HasNext() const;
        TItem Next();

      private:
        I32 position_;
        const List<TItem>& list_;
    };

    friend class Iterator;

  private:
    I32 capacity_;
    I32 length_;
    TItem* data_;
    void Initialize();
    void Cleanup();
    void Resize(I32 new_capacity);
};

template <typename TItem>
inline List<TItem>::List()
    : capacity_(4) {
  Initialize();
}

template <typename TItem>
inline List<TItem>::List(I32 capacity)
    : capacity_(capacity) {
  Initialize();
}

template <typename TItem>
inline List<TItem>::~List() {
  Cleanup();
}

template <typename TItem>
inline I32 List<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline I32 List<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline BOOL List<TItem>::IsEmpty() const {
  return length_ == 0;
}

template <typename TItem>
inline TItem List<TItem>::Get(I32 index) const {
  assert(index >= 0 && index < length_ && "index out of range");
  return data_[index];
}

template <typename TItem>
inline void List<TItem>::Set(I32 index, TItem item) {
  assert(index >= 0 && index < length_ && "index out of range");
  data_[index] = item;
}

template <typename TItem>
inline void List<TItem>::Add(TItem item) {
  if (length_ == capacity_) {
    I32 new_capacity = 2 * capacity_ + 1;
    Resize(new_capacity);
  }
  data_[length_++] = item;
}

template <typename TItem>
inline BOOL List<TItem>::Contains(TItem item) const {
  for (I32 i = 0; i < length_; ++i) {
    if (data_[i] == item) {
      return true;
    }
  }
  return false;
}

template <typename TItem>
inline I32 List<TItem>::IndexOf(TItem item) const {
  for (I32 i = 0; i < length_; ++i) {
    if (data_[i] == item) {
      return i;
    }
  }
  return -1;
}

template <typename TItem>
inline BOOL List<TItem>::Remove(TItem item) {
  I32 index = IndexOf(item);
  if (index != -1) {
    length_--;
    while (index < length_) {
      data_[index] = data_[index + 1];
      index++;
    }
    return true;
  }
  return false;
}

template <typename TItem>
inline void List<TItem>::Insert(I32 index, TItem item) {
  assert(index >= 0 && index <= length_ && "index out of range");
  Add(item);
  for (I32 i = length_ - 1; i > index; --i) {
    data_[i] = data_[i - 1];
  }
  data_[index] = item;
}

template <typename TItem>
inline void List<TItem>::Clear() {
  Cleanup();
  Initialize();
}

template <typename TItem>
inline TItem& List<TItem>::operator[] (I32 index) const {
  assert(index >= 0 && index < length_ && "index out of range");
  return data_[index];
}

template <typename TItem>
inline void List<TItem>::Initialize() {
  length_ = 0;
  data_ = new TItem[capacity_];
}

template <typename TItem>
inline void List<TItem>::Cleanup() {
  delete[] data_;
}

template <typename TItem>
inline void List<TItem>::Resize(I32 new_capacity) {
  TItem* new_data = new TItem[new_capacity];
  memcpy(new_data, data_, capacity_ * sizeof(TItem));
  Cleanup();
  data_ = new_data;
  capacity_ = new_capacity;
}

template <typename TItem>
inline List<TItem>::Iterator::Iterator(const List<TItem>& list)
    : position_(0),
      list_(list) {
}

template <typename TItem>
inline List<TItem>::Iterator::~Iterator() {
}

template <typename TItem>
inline BOOL List<TItem>::Iterator::HasNext() const {
  return position_ < list_.length();
}

template <typename TItem>
inline TItem List<TItem>::Iterator::Next() {
  return list_.data_[position_++];
}

}

#endif