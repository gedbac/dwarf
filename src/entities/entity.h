#ifndef DWARF_ENTITIES_ENTITY_H_
#define DWARF_ENTITIES_ENTITY_H_

#include "dwarf.h"

namespace dwarf {

class Entity {
  public:
    Entity(const I32 id);
    virtual ~Entity();
    I32 id() const;
    virtual void Update() = 0;

  private:
    I32 id_;
};

}

#endif