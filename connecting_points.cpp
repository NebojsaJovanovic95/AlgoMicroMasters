#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::queue;
using std::vector;
using std::sort;

struct edge {
    size_t u, v;
    double d;
};

bool cmp(edge a, edge b) {
    return a.d < b.d;
}

size_t find(size_t index, vector<size_t> &disjoint_sets) {
    if (index == -1)
        return index;
    queue<size_t> update;
    while (disjoint_sets[index] != -1) {
        update.push(index);
        index = disjoint_sets[index];
    }
    while (!update.empty()) {
        disjoint_sets[update.front()] = index;
        update.pop();
    }
    return index;
}

void unite(size_t a, size_t b, vector<size_t> &disjoint_sets) {
    disjoint_sets[find(a, disjoint_sets)] = find(b, disjoint_sets);
    return;
}

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
  //vector<vector<float>> distance(x.size(), vector<int>(x.size(), (float) 0));
  vector<edge> e;
  for (size_t i = 0; i < x.size(); i ++) {
    for (size_t j = 0; j < i; j ++) {
      double d = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      edge new_edge;
      new_edge.u = i;
      new_edge.v = j;
      new_edge.d = d;
      e.push_back(new_edge);
    }
  }
  sort(e.begin(), e.end(), cmp);
  //sorted my edges
  vector<size_t> disjoint_sets(x.size(), -1);
  // -1 means Null and the value shows which index is its parent
  //i need to initialize an empty set, I choose the node 0 as the root, fuck it all
  for (size_t i = 0; i < e.size(); i ++) {
    if (find(e[i].u, disjoint_sets) != find(e[i].v, disjoint_sets)) {
      result += e[i].d;
      unite(e[i].u, e[i].v, disjoint_sets);
    }
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
