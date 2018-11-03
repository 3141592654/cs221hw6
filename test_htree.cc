/*
 * Tests htree.cc.
 */

#include <assert.h>
#include <iostream>
#include "htree.hh"

int main() {
  std::cout << "INITIALIZING..." << std::endl;
  HTree::tree_ptr_t lrl = std::shared_ptr<const HTree>(new HTree(9, 8));
  HTree::tree_ptr_t lr = std::shared_ptr<const HTree>(new HTree(6, 5, lrl));
  HTree::tree_ptr_t ll = std::shared_ptr<const HTree>(new HTree(12, 11));
  HTree::tree_ptr_t l = std::shared_ptr<const HTree>(new HTree(-5, -6, ll, lr));
  HTree::tree_ptr_t rl = std::shared_ptr<const HTree>(new HTree(3, 2));
  HTree::tree_ptr_t r = std::shared_ptr<const HTree>(new HTree(12, 11, rl));
  HTree::tree_ptr_t root = std::shared_ptr<const HTree>
                             (new HTree(126, 125, l , r));

  std::cout << "RUNNING BASIC TESTS" << std::endl;
  assert(root->get_key() == 126);
  assert(root->get_value() == 125);
  assert(root->get_child(HTree::Direction::LEFT)->
    get_child(HTree::Direction::RIGHT)->get_key() == 6);
  assert(root->get_child(HTree::Direction::RIGHT)->
    get_child(HTree::Direction::LEFT)->
    get_child(HTree::Direction::RIGHT) == nullptr);

  std::cout << "RUNNING PATH_TO TESTS" << std::endl;
  HTree::path_t p = std::list<HTree::Direction>();
  assert(root->path_to(126) == p);
  assert(root->path_to(-5) != p);
  p.push_front(HTree::Direction::LEFT);
  assert(root->path_to(-5) == p);
  p.push_front(HTree::Direction::LEFT);
  assert(root->path_to(12) == p);
  p.pop_back();
  p.push_front(HTree::Direction::RIGHT);  // too lazy to get insert working
  p.push_front(HTree::Direction::LEFT);
  assert(root->path_to(9) == p);
  p.pop_back();
  assert(root->path_to(6) == p);
  p.pop_back();
  p.push_front(HTree::Direction::RIGHT);
  assert(root->path_to(3) == p);
  p.pop_front();
  assert(l->path_to(12) == p);
  // htree does not include node_at

  std::cout << "RUNNING DELETION TEST (CHECK VALGRIND)" << std::endl;
  return 0;
}
