#include <iostream>
using namespace std;
int get_change(int m) {
 //write your code here
 int curency[3] = {1, 3, 4};
 //for (int i = 0; i < 3; i ++) cout << curency[i]<<"\n";
 int change[m + 1];
 change[0] = 0;
 for (int i = 1; i <= m; i ++) {
  int min = 2 * i;
  for (int j = 0; j < 3; j ++)
   if (i - curency[j] >= 0)
    if (change[i - curency[j]] + 1 < min)
     min = change[i - curency[j]] + 1;
  change[i] = min;
 }
 //for (int i =  0; i < m + 1; i ++) cout<< change[i] << "\n";
 return change[m];
}

int main() {
 int m;
 cin >> m;
 cout << get_change(m) << '\n';
}