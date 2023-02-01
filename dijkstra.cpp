#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;
using std::greater;
using std::pair;
using std::make_pair;


int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  int result = -1;
  vector<int> dist(adj.size(), -1);
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
  q.push(make_pair(s, 0));
  while (!q.empty()) {
    pair<int, int> par = q.top();
    int x = par.first;
    int d = par.second;
    q.pop();
    if (x == t) {
        result = d;
        break;
    }
    for (size_t i = 0; i < adj[x].size(); i ++)
      if (dist[adj[x][i]] == -1)
        q.push(make_pair(adj[x][i], d + cost[x][i]));
    dist[x] = d;
  }
  return result;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
