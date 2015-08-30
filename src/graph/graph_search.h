#ifndef DWARF_GRAPH_GRAPH_SEARCH_H_
#define DWARF_GRAPH_GRAPH_SEARCH_H_

#include "dwarf.h"
#include "shared/list.h"

namespace dwarf {

class GraphSearch {
  public:
    virtual ~GraphSearch();
    virtual BOOL found() const;
    virtual I32 source() const;
    virtual void set_source(I32 source);
    virtual I32 target() const;
    virtual void set_target(I32 target);
    virtual BOOL Find() = 0;
    virtual const List<I32>& GetPath() = 0;
    virtual void Clear();

  protected:
    GraphSearch();
    virtual void set_found(BOOL found);

  private:
    BOOL found_;
    I32 source_;
    I32 target_;
};

inline GraphSearch::GraphSearch()
    : found_(false),
      source_(-1),
      target_(-1) {
}

inline GraphSearch::~GraphSearch() {}

inline BOOL GraphSearch::found() const {
  return found_;
}

inline void GraphSearch::set_found(BOOL found) {
  found_ = found;
}

inline I32 GraphSearch::source() const {
  return source_;
}

inline void GraphSearch::set_source(I32 source) {
  source_ = source;
}

inline I32 GraphSearch::target() const {
  return target_;
}

inline void GraphSearch::set_target(I32 target) {
  target_ = target;
}

inline void GraphSearch::Clear() {
  found_ = false;
  source_ = -1;
  target_ = -1;
}

}

#endif