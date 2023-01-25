#include <iostream>
#include <vector>

using std::vector;
using namespace std;

/*long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  //write your code here
  return number_of_inversions;
}*/

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

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << merge_sort(a, 0, a.size() - 1) << '\n';
}
