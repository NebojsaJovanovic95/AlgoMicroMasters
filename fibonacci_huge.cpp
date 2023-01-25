#include <iostream>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
 	if (n <= 1) return n;
 	long long first = 0;
 	long long second = 1;
 	long long period = 2;
 	for (long long i = 2; i <= n; i ++) {
    	long long pom = first;
     	first = second;
     	second = (second + pom) % m;
     	if (first == 0 && second == 1) {
         	period --;
         	break;
        }
     	period ++;
    }
 	long long pisano[period];
	period = 2;
 	pisano[0] = first;
 	pisano[1] = second;
 	first = 0;
 	second = 1;
 	for (long long i = 2; i <= n; i ++) {
    	long long pom = first;
     	first = second;
     	second = (second + pom) % m;
     	if (first == 0 && second == 1) {
         	period --;
         	break;
        }
     	pisano[i] = second;
     	period ++;
    }
 	long long result_index = n % period;
 	//std::cout << period << " " << result_index << '\n';
 	return pisano[result_index];
}

int main() {
    long long n, m;
    std::cin >> n >> m;
 	//std::cout << get_fibonacci_huge_naive(n, m) << '\n';
	std::cout << get_fibonacci_huge_fast(n, m) << '\n';
 	return 0;
}
