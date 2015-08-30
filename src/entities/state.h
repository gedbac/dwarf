#ifndef DWARF_ENTITIES_STATE_H_
#define DWARF_ENTITIES_STATE_H_

namespace dwarf {

template <typename TEntity>
class State {
  public:
    typedef TEntity EntityType;
    State();
    virtual ~State();
    virtual void Enter(TEntity& entity) = 0;
    virtual void Execute(TEntity& entity) = 0;
    virtual void Exit(TEntity& entity) = 0;
};

template <typename TEntity>
inline State<TEntity>::State() {}

template <typename TEntity>
inline State<TEntity>::~State() {}

}

#endif