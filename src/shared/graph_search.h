#ifndef DWARF_SHARED_GRAPH_SEARCH_H_
#define DWARF_SHARED_GRAPH_SEARCH_H_

#include "list.h"

namespace dwarf {
namespace shared {

class GraphSearch {
  public:
    virtual ~GraphSearch();
	virtual bool found() const = 0;
  	virtual int source() const = 0;
	virtual void set_source(int source) = 0;
	virtual int target() const = 0;
	virtual void set_target(int target) = 0;
    virtual bool Find() = 0;
	virtual const List<int>& GetPath() const = 0;
	// TODO: method 'Clear' has to be added
};

inline GraphSearch::~GraphSearch() {}

}
}

#endif