#ifndef DWARF_SHARED_COMPARER_H_
#define DWARF_SHARED_COMPARER_H_

#include "dwarf.h"

namespace dwarf {

template <typename TItem>
class Comparer {
  public:
    typedef TItem ItemType;
	  Comparer();
    Comparer(const BOOL inverse);
	  virtual ~Comparer();
 	  virtual I32 Compare(TItem& a, TItem& b) const;

  private:
    const BOOL inverse_;
};

template <typename TItem>
inline Comparer<TItem>::Comparer()
    : inverse_(false) {}

template <typename TItem>
inline Comparer<TItem>::Comparer(const BOOL inverse)
    : inverse_(inverse) {}

template <typename TItem>
inline Comparer<TItem>::~Comparer() {}

template <typename TItem>
inline I32 Comparer<TItem>::Compare(TItem& a, TItem& b) const {
  if (!inverse_) {
    if (a < b) {
      return 1;
    } else if (a > b) {
      return -1;
    }
  } else {
    if (a > b) {
      return 1;
    } else if (a < b) {
      return -1;
    }
  }
  return 0;
}

}

#endif