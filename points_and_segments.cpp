#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using namespace std;

//using my merge_sort from that inversions problem
// it stil computes inversions, but I don't care
long long merge_sort(vector<int> &a, int left, int right) {
 // we return from the tail end and give a coutn of inversions
 if (left + 1 >= right){
  if (a[left] > a[right]) {
   int pom = a[left];
   a[left] = a[right];
   a[right] = pom;
   return 1;
  } else return 0;
 }
 int split = left + (right - left) / 2;
 long long inversions = merge_sort(a, left, split) + merge_sort(a, split + 1, right);
 // copy the two parts into new vectors
 vector<int> left_vector(split - left + 1);
 vector<int> right_vector(right - split + 1);
 for (int i = left; i <= split; i ++)
  left_vector[i - left] = a[i];
 for (int i = split + 1; i <= right; i ++)
  right_vector[i - split - 1] = a[i];
 // now i copy the appropriate value into new vector and increase my counter
 int current = left;
 int left_itr = 0;
 int right_itr = 0;
 while (left_itr < split - left + 1 && right_itr < right - split) {
  if (left_vector[left_itr] > right_vector[right_itr]) {
   a[current] = right_vector[right_itr];
   inversions += split + 1 - left - left_itr;
   //this is how many I am skipping
   current ++;
   right_itr ++;
  } else {
   a[current] = left_vector[left_itr];
   current ++;
   left_itr ++;
  }
 }
 // we need to copy the leftover of the two vectors into vector a
 if (left_itr >= split - left + 1) {
  while (current <= right) {
   a[current] = right_vector[right_itr];
   current ++;
   right_itr ++;
  }
 }
 if (right_itr >= right - split) {
  while (current <= right) {
   a[current] = left_vector[left_itr];
   current ++;
   left_itr ++;
  }
 }
 //we are done with sorting and counting inversions
 /*for (int i = 0; i < a.size(); i ++) {
  cout << a[i] << " ";
 }
 cout << "\n";
 cout << left << " " << right << "\n";
 cout << inversions << "\n";
 */
 return inversions;
}

pair<int, int> bin_search (vector<int> a, int x) {
 // modified binary seach thet would find after which element in sorted a would x fit
 int left = 0, right = a.size() - 1;
 bool left_condition = false;
 bool right_condition = false;
 if (x < a[left]) return make_pair(-1, 0);
 else if (x > a[right]) return make_pair(right, 0);
 int index = -1;
 int msg = 0; // 0 for !+= 1 for ==
 while (true) {
  // iteration
  if (left + 1 >= right) {
   if (x >= a[left]) {
    if (x >= a[right])
     left = right;
    left_condition = true;
    right_condition = true;
   }
   else return make_pair(-1, 0);
  }
  index = (left + right) / 2;
  if (x == a[index]) {
   left_condition = true;
   right_condition = true;
   msg = 1;
  } else if (x > a[index]) {
   left = index;
  } else {
   right = index - 1;
  }
  if (left_condition && right_condition)
   break;
 }
 if (x == a[left]){
  index = left;
  msg = 1;
 }
 return make_pair(index, msg);
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
 vector<int> cnt(points.size());
 //write your code here
 // we sort starts and ends
 // we then find with binary search after which start our point would fit
 // we find after which end our point would fit
 // compute the cnt as the difference between those 2 indexes
 long long trash = merge_sort(starts, 0, starts.size() - 1);
 trash = merge_sort(ends, 0, ends.size() - 1);
 /*for (int i = 0; i < starts.size(); i ++)
  cout << starts[i] << " ";
 cout << "\n";*/
 //now I have sorted array and I can bin search
 for (int i = 0; i < points.size(); i ++) {
  pair<int, int> start = bin_search(starts, points[i]);
  if (start.first == -1) {
   cnt[i] = 0;
   // cout << start.first << " " << "?" << "\n";
   continue;
  }
  while (start.first < starts.size() - 1)
   if (starts[start.first + 1] == starts[start.first] && points[i] == starts[start.first + 1])
    start.first ++;
   else break;
  pair<int, int> end = bin_search(ends, points[i]);
  while (end.first > 0)
   if (ends[end.first - 1] == ends[end.first] && points[i] == ends[end.first - 1])
    end.first --;
   else break;
  // after how many starts am I - after how many ends am I
   //cout << start.first << " " << end.first << "\n";
  if (end.first == -1){
   cnt[i] = start.first + 1;
   continue;
  }
  cnt[i] = start.first + 1 - (end.first + 1 - end.second);
 }
 return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }/*
  vector<int> cnt = naive_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }*/
}
