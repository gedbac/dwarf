#ifndef DWARF_SHARED_LIST_H_
#define DWARF_SHARED_LIST_H_

namespace dwarf {
namespace shared {

#include <string.h>
#include <assert.h>

template <typename TItem>
class List {
  public:
    typedef TItem ItemType;
    List();
    List(int capacity);
    ~List();
    int capacity() const;
    int length() const;
    bool IsEmpty() const;
    TItem Get(int index) const;
    void Set(int index, TItem item);
    void Add(TItem item);
    bool Contains(TItem item) const;
    int IndexOf(TItem item) const;
    bool Remove(TItem item);
    void Insert(int index, TItem item);
    void Clear();
    TItem& operator[] (int index) const;

    class Iterator {
      public:
        Iterator(const List<TItem>& list);
        ~Iterator();
        bool HasNext() const;
        TItem Next();

      private:
        int position_;
        const List<TItem>& list_;
    };

    friend class Iterator;

  private:
    int capacity_;
    int length_;
    TItem* data_;
    void Initialize(int capacity);
    void Cleanup(TItem* data);
    void Resize(int new_capacity);
};

template <typename TItem>
inline List<TItem>::List()
    : capacity_(4) {
  Initialize(capacity_);
}

template <typename TItem>
inline List<TItem>::List(int capacity)
    : capacity_(capacity) {
  Initialize(capacity_);
}

template <typename TItem>
inline List<TItem>::~List() {
  Cleanup(data_);
}

template <typename TItem>
inline int List<TItem>::capacity() const {
  return capacity_;
}

template <typename TItem>
inline int List<TItem>::length() const {
  return length_;
}

template <typename TItem>
inline bool List<TItem>::IsEmpty() const {
  return length_ == 0;
}

template <typename TItem>
inline TItem List<TItem>::Get(int index) const {
  assert(index >= 0 && index < length_ && "index out of range");
  return data_[index];
}

template <typename TItem>
inline void List<TItem>::Set(int index, TItem item) {
  assert(index >= 0 && index < length_ && "index out of range");
  data_[index] = item;
}

template <typename TItem>
inline void List<TItem>::Add(TItem item) {
  if (length_ == capacity_) {
    int new_capacity = 2 * capacity_ + 1;
    Resize(new_capacity);
  }
  data_[length_++] = item;
}

template <typename TItem>
inline bool List<TItem>::Contains(TItem item) const {
  for (int i = 0; i < length_; ++i) {
    if (data_[i] == item) {
      return true;
    }
  }
  return false;
}

template <typename TItem>
inline int List<TItem>::IndexOf(TItem item) const {
  for (int i = 0; i < length_; ++i) {
    if (data_[i] == item) {
      return i;
    }
  }
  return -1;
}

template <typename TItem>
inline bool List<TItem>::Remove(TItem item) {
  int index = IndexOf(item);
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
inline void List<TItem>::Insert(int index, TItem item) {
  assert(index >= 0 && index <= length_ && "index out of range");
  Add(item);
  for (int i = length_ - 1; i > index; --i) {
    data_[i] = data_[i - 1];
  }
  data_[index] = item;
}

template <typename TItem>
inline void List<TItem>::Clear() {
  Cleanup(data_);
  Initialize(capacity_);
}

template <typename TItem>
inline TItem& List<TItem>::operator[] (int index) const {
  assert(index >= 0 && index < length_ && "index out of range");
  return data_[index];
}

template <typename TItem>
inline void List<TItem>::Initialize(int capacity) {
  length_ = 0;
  data_ = new TItem[capacity];
}

template <typename TItem>
inline void List<TItem>::Cleanup(TItem* data) {
  delete[] data;
}

template <typename TItem>
inline void List<TItem>::Resize(int new_capacity) {
  TItem* new_data = new TItem[new_capacity];
  memcpy(new_data, data_, capacity_ * sizeof(TItem));
  Cleanup(data_);
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
inline bool List<TItem>::Iterator::HasNext() const {
  return position_ < list_.length();
}

template <typename TItem>
inline TItem List<TItem>::Iterator::Next() {
  return list_.data_[position_++];
}

}
}

#endif