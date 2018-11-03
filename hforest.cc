/*
 * Implementation of hforest.hh.
 */

#include <assert.h>
#include <memory>
#include <algorithm>
#include <list>
#include "hforest.hh"
#include "htree.hh"

// constructor
HForest::HForest(std::vector<tree_ptr_t> forest) {
  // an attempt to pass nullptr into forest will not compile,
  // so we needn't worry that forest might be nullptr.
  forest_ = forest;
  std::make_heap(forest_.begin(), forest_.end(), compare_trees);
}

// destructor
HForest::~HForest() {
  // all the variables are shared pointers, so there's nothing to do here
}

int HForest::size() const {
  // forest_ is set to forest, which is guaranteed to not be nullptr
  return forest_.size();
}

void HForest::add_tree(tree_ptr_t t) {
  if (t != nullptr) {
    forest_.push_back(t);
    std::make_heap(forest_.begin(), forest_.end(), compare_trees);
  }
}

HForest::tree_ptr_t HForest::pop_tree() {
  if (size() == 0) {
    return nullptr;
  }
  HForest::tree_ptr_t result = forest_.front();
  forest_.erase(forest_.begin());
  std::make_heap(forest_.begin(), forest_.end(), compare_trees);
  return result;
}

// provided function with minor edits
bool compare_trees(HForest::tree_ptr_t t1, HForest::tree_ptr_t t2) {
  return t1->get_value() < t2->get_value();
}

