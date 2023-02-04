#include <iostream>
#include <vector>

using std::vector;

#define INFINITY 1e9

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  vector<int> prev(adj.size());
  vector<int> relaxed(adj.size());
  vector<int> dist(adj.size());
  for (size_t u = 0; u < adj.size(); u ++) {
    dist[u] = INFINITY;
    prev[u] = -1; // prev[u] = -1 represents null
    relaxed[u] = -1;
  }
  int last_relax = 0;

  for (size_t s = 0; s < adj.size(); s ++) {
    if (dist[s] != INFINITY)
      continue;
    dist[s] = 0;
    for (size_t i = 0; i < adj.size(); i ++) {
      for (size_t u = 0; u < adj.size(); u ++) {
        for (size_t v = 0; v < adj[u].size(); v ++) {
          //relax(u,v)
          if (dist[adj[u][v] ] > dist[u] + cost[u][v]) {
            dist[adj[u][v]] = dist[u] + cost[u][v];
            prev[adj[u][v]] = u;
            relaxed[u] = i;
          }
        }
        //std::cout << dist[u] << " ";
      }
      //std::cout << "\n";
    }
    for (size_t u = 0; u < adj.size(); u ++) {
      for (size_t v = 0; v < adj[u].size(); v ++) {
        //relax(u,v)
        if (dist[adj[u][v] ] > dist[u] + cost[u][v]) {
          dist[adj[u][v]] = dist[u] + cost[u][v];
          prev[adj[u][v]] = u;
          relaxed[u] = adj.size();
          last_relax = 1;
        }
      }
    }
  }


  //std::cout << prev[0];
  return last_relax;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
