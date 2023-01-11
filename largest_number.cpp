#include <iostream>

using namespace std;

int digit_cmp(int a, int b) {
 //1 if a >= b;
 int dec_a = 1;
 while (dec_a <= a) dec_a *= 10;
 int dec_b = 1;
 while (dec_b <= b) dec_b *= 10;
 //cout << dec_a << " " << dec_b << '\n';
 //now we compare it digit wise
 while (dec_a >= 10 && dec_b >= 10) {
  if ( (b % dec_b) / (dec_b / 10) > (a % dec_a) / (dec_a / 10) ) return 0;
  else if ( (b % dec_b) / (dec_b / 10) == (a % dec_a) / (dec_a / 10) ) {
   if (dec_a > dec_b) dec_a /= 10;
   else if (dec_a < dec_b) dec_b /= 10;
   else {
    dec_a /= 10;
    dec_b /= 10;
   }
  }
  else return 1;
 }
 if (a >= b) return 1;
 else return 0;
}

int main() {
 int n;
 std::cin >> n;
 int a[n];
 for (int i = 0; i < n; i++) {
  std::cin >> a[i];
 }
 //sort by digit size
 for (int i = 0; i < n - 1; i ++)
  for (int j = i + 1; j < n; j ++)
   if (digit_cmp(a[j], a[i]) == 1) {
    int pom = a[i]; 
    a[i] = a[j];
    a[j] = pom;
   }
 for (int i = 0; i < n; i ++)
  cout<<a[i];
}
