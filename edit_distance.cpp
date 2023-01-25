#include <iostream>
#include <string>

using std::string;
using namespace std;

int edit_distance(const string &str1, const string &str2) {
 //write your code here
 int len1 = str1.size();
 int len2 = str2.size();
 int distance[len1 + 1][len2 + 1];
 int method[len1 + 1][len2 + 1];
 for (int i = 0; i <= len1; i ++) {
  distance[i][0] = i;
  method[i][0] = 1;
 }
 for (int i = 0; i <= len2; i ++) {
  distance[0][i] = i;
  method[0][i] = 3;
 }
 int i = 1, j = 1;
 for (j  = 1; j <= len2; j ++)
  for (i = 1; i <= len1; i ++) {
  //we check who is the smallest
  int mismatch = distance[i - 1][j - 1] + 1;
  int insertion = distance[i][j - 1] + 1;
  int match = distance[i - 1][j - 1];
  int deletion = distance[i-1][j] + 1;
  int min = insertion;
  int met = 1;
  if (deletion < min) {
   min = deletion;
   met = 3;
  }
  if (str1[i - 1] == str2[j - 1]) {
   if (match < min){
    min = match;
    met = 2;
   }
  }
  else {
   if (mismatch < min) {
    min = mismatch;
    met = 0;
   }
  }
  distance[i][j] = min;
  method[i][j] = met;
 }
 /*for (int i = 0; i <= len1; i ++){
  for (int j = 0; j <= len2; j ++)
   cout << distance[i][j] << " ";
  cout << "\n";
 }*/
 int result = distance[len1][len2];
 return result;
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
