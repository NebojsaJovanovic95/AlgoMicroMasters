#include <iostream>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

long long fibonacci_sum_fast(long long n) {
 	if (n <= 1) return n;
 	long long m = 10;
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
 	long long pisano_sum[period];
 	pisano_sum[0] = 0;
 	pisano_sum[1] = 1;
 	for (long long i = 2; i <= n; i ++) {
    	long long pom = first;
     	first = second;
     	second = (second + pom) % m;
     	if (first == 0 && second == 1) {
         	period --;
         	break;
        }
     	pisano[i] = second;
     	pisano_sum[i] = pisano_sum[i-1] + second;
     	period ++;
    }
 	long long periods = n / period;
 	long long result_index = n % period;
 	long long result = periods * pisano_sum[period - 1] + pisano_sum[result_index];
 	//std::cout << period << " " << result_index << '\n';
 	return result % 10;
}

int main() {
    long long n = 0, nj = 0;
    std::cin >> nj >> n;
    std::cout << (10 + fibonacci_sum_fast(n) - fibonacci_sum_fast(nj - 1) ) % 10;
}
