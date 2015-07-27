#ifndef DWARF_SHARED_COMPARER
#define DWARF_SHARED_COMPARER

namespace dwarf {
namespace shared {

template <typename TItem>
class Comparer {
  public:
    typedef TItem ItemType;
	  Comparer();
    Comparer(const bool inverse);
	  ~Comparer();
 	  int Compare(TItem& a, TItem& b) const;

  private:
    const bool inverse_;
};

template <typename TItem>
inline Comparer<TItem>::Comparer()
    : inverse_(false) {}

template <typename TItem>
inline Comparer<TItem>::Comparer(const bool inverse)
    : inverse_(inverse) {}

template <typename TItem>
inline Comparer<TItem>::~Comparer() {}

template <typename TItem>
inline int Comparer<TItem>::Compare(TItem& a, TItem& b) const {
  if (!inverse_) {
    if (a < b) {
      return -1;
    } else if (a > b) {
      return 1;
    }
  } else {
    if (a > b) {
      return -1;
    } else if (a < b) {
      return 1;
    }
  }
  return 0;
}

}
}

#endif