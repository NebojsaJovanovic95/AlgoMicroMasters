#include <iostream>
#include <vector>

using std::vector;
using namespace std;

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
 vector<int> cnt(points.size());
 //write your code here
 //initialize a primitive map mapping 1 where begin is and -1 where end is and 0 else
 //use the first primitivemap to build a primitive map that says for location x how many
 //segments it is in
 const int e8 = 1e8;
 int count_begin[2 * e8 + 1];
 int count_end[2 * e8 + 1];
 int score[2 * e8 + 1];
 
 for (int i = 0; i < 2 * e8 + 1; i ++) {
  count_begin[i] = 0;
  count_end[i] = 0;
  score[i] = 0;
 }
 int n = starts.size();
 for (int i = 0; i < n; i ++) {
  count_begin[starts[i] - e8] ++;
  count_end[ends[i] - e8] ++;
 }
 
 int current_begin = 0;
 int current_end = 0;
 for (int i = 0; i < 2 * e8; i ++) {
  current_begin += count_begin[i];
  score[i] = current_begin - current_end;
  current_end += count_end[i];
  //the start is before the field and end is after the field
  //this addresses the begins and ends that are in the same point
 }
 //now we make vector cnt and just read from our primitive map
 for (int i = 0; i < points.size(); i ++) {
  cnt[i] = score[points[i] - e8];
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
