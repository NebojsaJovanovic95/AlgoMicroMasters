#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
using namespace std;
using std::vector;

int get_majority_element(vector<int> &a) {
 //write your code here
 map<int, int> votes;
 int majority = 0;
 for (int i = 0; i < a.size(); i ++) {
  if (votes.find(a[i]) == votes.end()){
   votes.insert(pair<int, int>(a[i], 1) );
  } else {
   votes[a[i]] ++;
   if (votes[a[i]] > a.size() / 2) 
    majority = 1;
  }
 }
 //int majority_count = 0;
 map<int, int>::iterator itr;
 /*for (itr = votes.begin(); itr != votes.end(); itr ++) {
  cout << itr -> first << " " << itr -> second << '\n';
 }*/
 return majority;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << get_majority_element(a) << '\n';
}
