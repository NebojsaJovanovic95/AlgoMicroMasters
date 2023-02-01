#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using std::vector;
using std::queue;
using std::pair;
using std::make_pair;

void distance(vector<vector<int> > &adj, vector<int> &dist, int s) {
  //write your code here
  //vector<int> dist(adj.size(), -1);
  queue<pair<int, int> > q;
  q.push(make_pair(s, 0));
  while (!q.empty()) {
    auto [x, d] = q.front();
    for (auto next : adj[x])
      if (dist[next] == -1)
        q.push(make_pair(next, d + 1));
    dist[x] = d;
    q.pop();
  }
  return;
}


int bipartite(vector<vector<int> > &adj, vector<pair<int, int> > &edge) {
  //write your code here
  vector<int> dist(adj.size(), -1);
  for (size_t i = 0; i < adj.size(); i ++)
    if (dist[i] == -1)
      distance(adj, dist, i);
  // now all the vertices as initialized with some distance
  for (auto &[u, v] : edge)
    if (dist[u] % 2 == dist[v] % 2)
      return 0;
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<pair<int, int> > edge;
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
    edge.push_back(make_pair(x - 1, y - 1));
  }
  std::cout << bipartite(adj, edge);
}
