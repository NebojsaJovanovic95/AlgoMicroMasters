#include <iostream>
#include <vector>

using std::vector;
using namespace std;

int optimal_weight_greedy(int W, const vector<int> &w) {
  //write your code here
  int current_weight = 0;
  for (size_t i = 0; i < w.size(); ++i) {
    if (current_weight + w[i] <= W) {
      current_weight += w[i];
    }
  }
  return current_weight;
}

int optimal_weight (int W, const vector<int> &weight) {
 int n = weight.size();
 int *array_helper = new int[(W + 1)*(n + 1)];
 int (*value)[n + 1] = (int (*)[n + 1])array_helper;
 //int value[W + 1][n + 1];
 vector<int> v(n);
 for (int i = 0; i < n; i ++)
  v[i] = weight[i];
 for (int i = 0; i < W + 1; i ++)
  value[i][0] = 0;
 for (int i = 0; i < n + 1; i ++)
  value[0][i] = 0;
 for (int i = 1; i < n + 1; i ++) {
  for (int w = 1; w < W + 1; w ++) {
   value[w][i] = value[w][i - 1];
   if (weight[i - 1] <= w) {
    int val = value[w - weight[i - 1] ][i - 1] + v[i - 1];
    if (value[w][i] < val)
     value[w][i] = val;
   }
   //cout << value[w][i] << " ";
  }
  //cout << "\n";
 }
 int result = value[W][n];
 delete value;
 return result;
}

int main() {
  int n, W;
  std::cin >> W >> n;
 if (n <= 0) {
  cout << 0;
  return 0;
 }
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
