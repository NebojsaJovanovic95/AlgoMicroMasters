#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::tuple;
using std::get;
using std::make_tuple;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

tuple<bool, bool, int, int> is_bin(const vector<Node>& tree, int index) {
    if (index == -1)
        return make_tuple(true, true, 0, 0);
    // tuple is _is_tree _is_null _min _max
    int min = tree[index].key;
    int max = tree[index].key;
    tuple<bool, bool, int, int> left_tree = is_bin(tree, tree[index].left);
    if (!get<0>(left_tree))
        return make_tuple(false, false, 0, 0);
    else if (!get<1>(left_tree))
        if (get<3>(left_tree) > tree[index].key || get<2>(left_tree) > tree[index].key)
            return make_tuple(false, false, 0, 0);
        else if (get<2>(left_tree) < min)
            min = get<2>(left_tree);
    tuple<bool, bool, int, int> right_tree = is_bin(tree, tree[index].right);
    if (!get<0>(right_tree))
        return make_tuple(false, false, 0, 0);
    else if (!get<1>(right_tree))
        if (get<2>(right_tree) < tree[index].key || get<3>(right_tree) < tree[index].key)
            return make_tuple(false, false, 0, 0);
        else if (get<2>(right_tree) > max)
            max = get<2>(right_tree);
    // we now return the result
    return make_tuple(true, false, min, max);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  // check left check right
  if (tree.size() == 0)
    return true;
  tuple<bool, bool, int, int> root = is_bin(tree, 0);
  return get<0>(root);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
