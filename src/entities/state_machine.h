#ifndef DWARF_ENTITIES_STATE_MACHINE_H_
#define DWARF_ENTITIES_STATE_MACHINE_H_

#include <assert.h>

#include "dwarf.h"
#include "entities/state.h"

namespace dwarf {

template <typename TEntity>
class StateMachine {
  public:
    StateMachine(TEntity& owner);
    virtual ~StateMachine();
    TEntity& owner() const;
    State<TEntity>* global_state() const;
    void set_global_state(State<TEntity>* state);
    State<TEntity>* current_state() const;
    void set_current_state(State<TEntity>* state);
    State<TEntity>* previous_state() const;
    void set_previous_state(State<TEntity>* state);
    virtual void Update();
    virtual BOOL IsInState(State<TEntity>* state) const;
    virtual void ChangeState(State<TEntity>* state);
    virtual void RevertState();

  private:
    TEntity& owner_;
    State<TEntity>* global_state_;
    State<TEntity>* current_state_;
    State<TEntity>* previous_state_;
};

template <typename TEntity>
StateMachine<TEntity>::StateMachine(TEntity& owner)
    : owner_(owner) {}

template <typename TEntity>
StateMachine<TEntity>::~StateMachine() {}

template <typename TEntity>
TEntity& StateMachine<TEntity>::owner() const{
  return owner_;
}

template <typename TEntity>
State<TEntity>* StateMachine<TEntity>::global_state() const {
  return global_state_;
}

template <typename TEntity>
void StateMachine<TEntity>::set_global_state(State<TEntity>* state) {
  global_state_ = state;
}

template <typename TEntity>
State<TEntity>* StateMachine<TEntity>::current_state() const {
  return current_state_;
}

template <typename TEntity>
void StateMachine<TEntity>::set_current_state(State<TEntity>* state) {
  current_state_ = state;
}

template <typename TEntity>
State<TEntity>* StateMachine<TEntity>::previous_state() const {
  return previous_state_;
}

template <typename TEntity>
void StateMachine<TEntity>::set_previous_state(State<TEntity>* state) {
  previous_state_ = state;
}

template <typename TEntity>
void StateMachine<TEntity>::Update() {
  if (global_state()) {
    global_state()->Execute(*owner());
  }
  if (current_state()) {
    current_state()->Execute(*owner());
  }
}

template <typename TEntity>
BOOL StateMachine<TEntity>::IsInState(State<TEntity>* state) const {
  return state == current_state();
}

template <typename TEntity>
void StateMachine<TEntity>::ChangeState(State<TEntity>* state) {
  set_previous_state(current_state());
  if (current_state()) {
    current_state()->Exit(*owner());
  }
  set_current_state(state);
  if (current_state()){
    current_state()->Enter(*owner());
  }
}

template <typename TEntity>
void StateMachine<TEntity>::RevertState() {
  ChangeState(previous_state());
}

}

#endif