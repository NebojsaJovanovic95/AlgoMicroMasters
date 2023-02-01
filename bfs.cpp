#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using std::vector;
using std::queue;
using std::pair;
using std::make_pair;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  int result = -1;
  vector<int> dist(adj.size(), -1);
  queue<pair<int, int> > q;
  q.push(make_pair(s, 0));
  while (!q.empty()) {
    pair<int, int> par = q.front();
    int x = par.first;
    int d = par.second;
    if (x == t) {
        result = d;
        break;
    }
    for (size_t i = 0; i < adj[x].size(); i ++)
      if (dist[adj[x][i]] == -1)
        q.push(make_pair(adj[x][i], d + 1));
    dist[x] = d;
    q.pop();
  }
  return result;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
