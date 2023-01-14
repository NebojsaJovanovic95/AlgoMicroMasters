#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility> // for pair
#include <math.h> // rand

using std::vector;
using std::swap;
using namespace std;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

pair<int, int> partition3(vector<int> &a, int l, int r) {
 int x = a[l];
 pair<int, int> zone = make_pair(l,l);
 //zone.first is the left bound of the equals zone
 //zone.right is the right bound of the equals zone
 for (int i = l + 1; i <= r; i ++) {
  if (a[i] < a[zone.first]) {
   swap(a[i], a[zone.second + 1]);
   swap(a[zone.first], a[zone.second + 1]);
   zone.first ++;
   zone.second ++;
  } else if (a[i] == x) {
   swap(a[i], a[zone.second + 1]);
   zone.second ++;
  }
 }
 /*cout<< l << " " << r << " " << x << " " << zone.first << " " << zone.second << "\n";
 for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
 cout << "\n";*/
 //swap(a[l], a[zone.first]);
 return zone;
}

void randomized_quick_sort2(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
 
  int m = partition2(a, l, r);

  randomized_quick_sort2(a, l, m - 1);
  randomized_quick_sort2(a, m + 1, r);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
 if (l >= r)
  return;
 
 int k = l + rand() % (r - l + 1);
 swap(a[l], a[k]);
 
 pair<int, int> zone = partition3(a, l, r);
 
 randomized_quick_sort(a, l, zone.first - 1);
 randomized_quick_sort(a, zone.second + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
