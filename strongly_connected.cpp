#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::pair;

int dfs(vector<vector<int> > adj, vector<int> &visited, stack<int> &post, int order, int x) {
  // we perform the searcg and label them for post order
  visited[x] = 1;
  for (size_t i = 0; i < adj[x].size(); i ++)
    if (visited[ adj[x][i] ] == 0)
      order = dfs(adj, visited, post, order, adj[x][i]);
  post.push(x);
  return order + 1;
}

int number_of_strongly_connected_components(vector<vector<int> > adj, vector<vector<int> > reverse) {
  int result = 0;
  //write your code here
  // reverse graph
  // ---> taken as an input due to time constraints
  //we find psot order in reverse graph
  vector<int> visited(adj.size(), 0);
  stack<int> post;
  int order = 1;
  for (size_t i = 0; i < adj.size(); i ++)
    if (visited[i] == 0)
        order = dfs(reverse, visited, post, order, i);
  //now we have everyones post order
  for (size_t i = 0; i < visited.size(); i ++)
    visited[i] = 0;
  stack<int> cc; // dummy stack
  while (!post.empty()) {
    int x = post.top();
    post.pop();
    if (visited[x] == 1)
      continue;
    order = dfs(adj, visited, cc, order, x);
    //now cc has all the connected components and we can mark them
    result ++;
  }
  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > reverse(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    reverse[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, reverse);
}
