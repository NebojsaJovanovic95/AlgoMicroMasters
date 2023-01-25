#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int tree_size (vector<int> &parent) {
 int n = parent.size();
 vector<int> visited_children(n);
 vector<stack<int> > children(n);
 stack<pair<int, int> > call;
 for (int i = 0; i < n; i ++)
  visited_children[i] = 0;
 int root = -1;
 for (int i = 0; i < n; i ++)
  if (parent[i] == -1)
   root = i;
  else
   children[parent[i]].push(i);
 // we have our tree organized and now we will work with stack to traverse it
 call.push(make_pair(root, 1));
 int max = 0;
 while (!call.empty() ) {
  pair<int, int> current_pair = call.top();
  int current = current_pair.first;
  int level = current_pair.second;
  //cout << current << " " << level << "\n";
  if (children[current].size() == 0) {
    if (level > max)
     max = level;
    call.pop();
  } else {
    while (!children[current].empty()) {
      call.push(make_pair(children[current].top(), level + 1) );
      children[current].pop();
    }
  }

 }

 return max;
}

int main (int argc, char **argv)
{
 int n;
 cin >> n;
 vector<int> parent(n);
 for (int i = 0; i < n; i ++) {
  cin >> parent[i];
 }

 cout << tree_size(parent);
}