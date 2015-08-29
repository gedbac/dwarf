#ifndef DWARF_GRAPH_GRAPH_SEARCH_H_
#define DWARF_GRAPH_GRAPH_SEARCH_H_

#include "list.h"

namespace dwarf {

class GraphSearch {
  public:
    virtual ~GraphSearch();
    virtual bool found() const;
    virtual int source() const;
    virtual void set_source(int source);
    virtual int target() const;
    virtual void set_target(int target);
    virtual bool Find() = 0;
    virtual const List<int>& GetPath() const = 0;
    virtual void Clear();

  protected:
    GraphSearch();
    virtual void set_found(bool found);

  private:
    bool found_;
    int source_;
    int target_;
};

inline GraphSearch::GraphSearch()
  : found_(false),
	source_(-1),
	target_(-1) {
}

inline GraphSearch::~GraphSearch() {}

inline bool GraphSearch::found() const {
  return found_;
}

inline void GraphSearch::set_found(bool found) {
  found_ = found;
}

inline int GraphSearch::source() const {
  return source_;
}

inline void GraphSearch::set_source(int source) {
  source_ = source;
}

inline int GraphSearch::target() const {
  return target_;
}

inline void GraphSearch::set_target(int target) {
  target_ = target;
}

inline void GraphSearch::Clear() {
  found_ = false;
  source_ = -1;
  target_ = -1;
}

}

#endif