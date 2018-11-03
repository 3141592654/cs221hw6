/*
 * Implementation of htree.hh.
 */

#include <assert.h>
#include <memory>
#include <list>
#include "htree.hh"

// constructor
HTree::HTree(int key, uint64_t value, HTree::tree_ptr_t left,
                                   HTree::tree_ptr_t right) {
  key_ = new int(key);
  value_ = new uint64_t(value);
  // shouldn't allocate new stuff for left and right. if left/right gets messed
  // up somewhere else, it should get messed up here too.
  left_ = left;
  right_ = right;
}

// destructor
HTree::~HTree() {
  delete key_;
  delete value_;
  // tree_ptr_t is a smart pointer, so left_ and right_ will delete themselves
}

// accessors. no getters. if there were both accessors and getters, the
// relevant variables should be public. right now these trees are read-only.
int HTree::get_key() const {
  return *key_;
}
uint64_t HTree::get_value() const {
  return *value_;
}
HTree::tree_ptr_t HTree::get_child(HTree::Direction dir) const {
  if (dir == HTree::Direction::LEFT) {
    return left_;
  } else {
    return right_;
  }
}

// implementation of value_found
bool HTree::value_found(HTree::path_t* result, const int key) const {
  if (get_key() == key) {
    return true;
  }
  // check if the key was found somewhere to the left of this parent node.
  // if so, make a note of it and return to the parent node.
  // also, get_child(HTree::Direction::LEFT) is far uglier than left_ and has
  // no difference in functionality. the prompt says to use it though.
  if (get_child(HTree::Direction::LEFT) != nullptr) {
    if (get_child(HTree::Direction::LEFT)->value_found(result, key)) {
      result->push_front(HTree::Direction::LEFT);
      return true;
    }
  }
  // check if key was found to right of this parent node.
  if (get_child(HTree::Direction::RIGHT)  != nullptr) {
    if (get_child(HTree::Direction::RIGHT)->value_found(result, key)) {
      result->push_front(HTree::Direction::RIGHT);
      return true;
    }
  }
  // if the code has gotten to this point, then this node
  // doesn't have the key, and neither do its children, so
  return false;
}

// implementation of path_to
HTree::path_t HTree::path_to(int key) const {
  HTree::path_t result = std::list<HTree::Direction>();
  assert(value_found(&result, key));
  return result;
}

