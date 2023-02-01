#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

int dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int index, int x) {
  //write your code here
  for (size_t i = 0; i < adj[x].size(); i ++)
    if (used[ adj[x][i] ] == 0)
      index = dfs(adj, used, order, index, adj[x][i]);
  order[index] = x;
  used[x] = 1;
  return index - 1;
}

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order(adj.size(), 0);
  //write your code here
  int index = used.size() - 1;
  for (size_t i = 0; i < used.size(); i ++)
    if (used[i] == 0)
      index = dfs(adj, used, order, index, i);
  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
