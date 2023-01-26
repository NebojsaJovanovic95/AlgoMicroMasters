#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  bool cmp (int index1, int index2) {
    if (index1 >= data_.size()) return true;
    else if (index2 >= data_.size()) return true;
    return data_[index1] <= data_[index2];
  }

  void swap_ (int index1, int index2) {
    swap(data_[index1], data_[index2]);
  }

  void sift_down (int index) {
    while (true) {
        // cout << index << " \n";
        int left = (index + 1) * 2 - 1;
        if (cmp(index, left) && cmp(index, left + 1))
            break;
        else if (cmp(left, left + 1)) {
            // we know index < index * 2
            swaps_.push_back(make_pair(index, left));
            swap_(index, left);
            index = left;
        } else {
            swaps_.push_back(make_pair(index, left + 1));
            swap_(index, left + 1);
            index = left + 1;
        }
    }
    return;
  }

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    // swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = data_.size() / 2; i >= 0; i --)
      sift_down(i);
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
