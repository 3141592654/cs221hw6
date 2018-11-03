/*
 * Tests hforest.cc.
 */

#include <assert.h>
#include <iostream>
#include <vector>
#include "hforest.hh"

void basic_forest_test(HForest myforest) {
  // the order of the heap is not guaranteed, but it is guaranteed that the
  // biggest one is first.
  HTree::tree_ptr_t root = myforest.forest_[0];
  assert(root->get_key() == 326);
  assert(root->get_value() == 325);
  assert(root->get_child(HTree::Direction::LEFT)->
    get_child(HTree::Direction::RIGHT)->get_key() == 6);
  assert(root->get_child(HTree::Direction::RIGHT)->
    get_child(HTree::Direction::LEFT)->
    get_child(HTree::Direction::RIGHT) == nullptr);

  root = myforest.forest_[0];
  HTree::path_t p = std::list<HTree::Direction>();
  assert(root->path_to(326) == p);
  assert(root->path_to(-5) != p);
  p.push_front(HTree::Direction::LEFT);
  assert(root->path_to(-5) == p);
  p.push_front(HTree::Direction::LEFT);
  assert(root->path_to(32) == p);
  p.pop_back();
  p.push_front(HTree::Direction::RIGHT);
  p.push_front(HTree::Direction::LEFT);
  assert(root->path_to(9) == p);
  p.pop_back();
  assert(root->path_to(6) == p);
  p.pop_back();
  p.push_front(HTree::Direction::RIGHT);
  assert(root->path_to(3) == p);
}

int main() {
  // make some big ol' trees
  HTree::tree_ptr_t lrl1 = std::shared_ptr<const HTree>(new HTree(9, 8));
  HTree::tree_ptr_t lr1 = std::shared_ptr<const HTree>(new HTree(6, 5, lrl1));
  HTree::tree_ptr_t ll1 = std::shared_ptr<const HTree>(new HTree(12, 11));
  HTree::tree_ptr_t l1 = std::shared_ptr<const HTree>
                       (new HTree(-5, -6, ll1, lr1));
  HTree::tree_ptr_t rl1 = std::shared_ptr<const HTree>(new HTree(3, 2));
  HTree::tree_ptr_t r1 = std::shared_ptr<const HTree>(new HTree(12, 11, rl1));
  HTree::tree_ptr_t root1 = std::shared_ptr<const HTree>
                          (new HTree(126, 125, l1, r1));

  HTree::tree_ptr_t lrl2 = std::shared_ptr<const HTree>(new HTree(9, 8));
  HTree::tree_ptr_t lr2 = std::shared_ptr<const HTree>(new HTree(6, 5, lrl2));
  HTree::tree_ptr_t ll2 = std::shared_ptr<const HTree>(new HTree(22, 22));
  HTree::tree_ptr_t l2 = std::shared_ptr<const HTree>
                       (new HTree(-5, -6, ll2, lr2));
  HTree::tree_ptr_t rl2 = std::shared_ptr<const HTree>(new HTree(3, 2));
  HTree::tree_ptr_t r2 = std::shared_ptr<const HTree>(new HTree(22, 22, rl2));
  HTree::tree_ptr_t root2 = std::shared_ptr<const HTree>
                          (new HTree(226, 225, l2, r2));

  HTree::tree_ptr_t lrl3 = std::shared_ptr<const HTree>(new HTree(9, 8));
  HTree::tree_ptr_t lr3 = std::shared_ptr<const HTree>(new HTree(6, 5, lrl3));
  HTree::tree_ptr_t ll3 = std::shared_ptr<const HTree>(new HTree(32, 33));
  HTree::tree_ptr_t l3 = std::shared_ptr<const HTree>
                       (new HTree(-5, -6, ll3, lr3));
  HTree::tree_ptr_t rl3 = std::shared_ptr<const HTree>(new HTree(3, 2));
  HTree::tree_ptr_t r3 = std::shared_ptr<const HTree>(new HTree(32, 33, rl3));
  HTree::tree_ptr_t root3 = std::shared_ptr<const HTree>
                          (new HTree(326, 325, l3, r3));

  // test default constructor
  HForest myforest;
  myforest.add_tree(root1);
  myforest.add_tree(root2);
  myforest.add_tree(root3);
  basic_forest_test(myforest);

  // test constructor from vector
  std::vector<HTree::tree_ptr_t> mfa(0);
  mfa.push_back(root1);
  mfa.push_back(root2);
  mfa.push_back(root3);
  HForest mf2(mfa);
  basic_forest_test(mf2);

  // now test deletion
  assert(myforest.pop_tree()->get_key() == 326);
  assert(myforest.size() == 2);
  assert(myforest.pop_tree()->get_key() == 226);
  assert(myforest.size() == 1);
  assert(myforest.pop_tree()->get_key() == 126);
  assert(myforest.size() == 0);
  // try to delete with no elements remaining
  assert(myforest.pop_tree() == nullptr);
  // try adding a nullptr
  myforest.add_tree(nullptr);
  assert(myforest.size() == 0);

  return 0;
}
