#include "entities/entity.h"

namespace dwarf {

Entity::Entity(const I32 id)
    : id_(id) {}

Entity::~Entity() {}

I32 Entity::id() const {
  return id_;
}

}