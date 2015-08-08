#ifndef DWARF_SHARED_GRAPH_SEARCH_H_
#define DWARF_SHARED_GRAPH_SEARCH_H_

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
};

inline GraphSearch::~GraphSearch() {}

}
}

#endif