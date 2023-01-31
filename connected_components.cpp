#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int reach(vector<vector<int> > &adj, vector<int> &visited, int x, int res) {
  //write your code here
  visited[x] = res;
  for (size_t i = 0; i < adj[x].size(); i ++)
    if (visited[ adj[x][i] ] == 0)
      reach(adj, visited, adj[x][i], res);
  return res;
}

int number_of_components(vector<vector<int> > &adj, vector<int> &visited) {
  int res = 1;
  //write your code here
  for (size_t i = 0; i < visited.size(); i ++)
    if (visited[i] == 0)
        res = reach(adj, visited, i, res) + 1;
  return res - 1;
}



int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<int> visited(n);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
    visited[x - 1] = 0;
    visited[y - 1] = 0;
  }
  std::cout << number_of_components(adj, visited);
}
