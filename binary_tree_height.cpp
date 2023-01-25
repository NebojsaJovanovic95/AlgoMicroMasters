#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int tree_size (vector<int> &parent) {
 int n = parent.size();
 vector<int> left(n), right(n), visited(n);
 stack<int> call;
 for (int i = 0; i < n; i ++) {
  left[i] = -1;
  right[i] = -1;
  visited[i] = 0;
 }
 int root = -1;
 for (int i = 0; i < n; i ++)
  if (parent[i] == -1)
   root = i;
  else if (left[parent[i] ] == -1)
   left[parent[i] ] = i;
  else if (right[parent[i] ] == -1)
   right[parent[i] ] = i;
 // we have our tree organized and now we will work with stack to traverse it
 call.push(root);
 int max = 0;
 int count = 0;
 while (!call.empty() ) {
  int current = call.top();
  bool child_visited = false;
  count ++;
  // cout << current << " " << count << "\n";
  if (right[current] == -1 && left[current] == -1) {
   //leaf node
   visited[current] = 1;
   if (count > max)
    max = count;
   count --;
   call.pop();
  }
  else if (right[current] == -1 && visited[left[current] ]) {
   child_visited = true;
  }
  else if (left[current] == -1 && visited[right[current] ]) {
   child_visited = true;
  }
  else if (visited[left[current] ] && visited[right[current] ]) {
   child_visited = true;
  } 
  if (child_visited) {
   visited[current] = 1;
   count --;
   count --;
   call.pop();
  }
  
  if (right[current] != -1 && visited[right[current] ] == 0)
   call.push(right[current]);
  if (left[current] != -1 && visited[left[current] ] == 0)
   call.push(left[current]);
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