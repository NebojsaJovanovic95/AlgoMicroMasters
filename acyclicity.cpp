#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int reach(vector<vector<int> > &adj, vector<int> &visited, int x, int key) {
  //write your code here
  if (visited[x] == 1)
    if (x == key)
        return 1;
    else return 0;
  visited[x] = 1;
  for (size_t i = 0; i < adj[x].size(); i ++)
    if (reach(adj, visited, adj[x][i], key) == 1)
      return 1;
  return 0;
}

int acyclic(vector<vector<int> > &adj, vector<int> &visited) {
  //write your code here
  for (size_t i = 0; i < visited.size(); i ++)
    if (visited[i] == 0)
      if (reach(adj, visited, i, i) == 1)
        return 1;
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<int> visited(n);
  for (size_t i = 0; i < m; i ++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  for (size_t i = 0; i < n; i ++)
    visited[i] = 0;
  std::cout << acyclic(adj, visited);
}
