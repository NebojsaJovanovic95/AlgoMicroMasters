#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using std::vector;
using std::cin;
using std::cout;
using namespace std;

class JobQueue {
 private:
  long long num_workers_;
  vector<long long> jobs_;

  vector<long long> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (long long i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    long long m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(long long i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  bool cmp (long long index1, long long index2, vector<tuple<long long, long long, long long, long long> > &heap, long long heap_size) {
    if (index1 >= heap_size) return true;
    else if (index2 >= heap_size) return true;
    if ( (get<2>(heap[index1]) + get<3>(heap[index1]) ) < (get<2>(heap[index2]) + get<3>(heap[index2]) ) )
      return true;
    else if ( (get<2>(heap[index1]) + get<3>(heap[index1]) ) == (get<2>(heap[index2]) + get<3>(heap[index2]) ) )
      return (get<0>(heap[index1]) < get<0>(heap[index2]));
    else return false;
  }

  void sift_down (long long index, vector<tuple<long long, long long, long long, long long> > &heap, long long heap_size) {
    //make it sift down the heap
    while (index < heap_size) {
      long long left = (index + 1) * 2 - 1;
      if (cmp(index, left, heap, heap_size) && cmp(index, left + 1, heap, heap_size))
        break;
      else if (cmp(left, left + 1, heap, heap_size)) {
        swap(heap[index], heap[left]);
        index = left;
      } else {
        swap(heap[index], heap[left + 1]);
        index = left + 1;
      }
    }
    return;
  }

  void show (vector<tuple<long long, long long, long long, long long> > &heap) {
    // works with index
    /*
    for (long long i = 0; i < heap.size(); i ++) {
      auto [worker, job, start_time, duration] = heap[i];
      cout << "worker: " << worker
           << ", job: " << job
           << ", start_time: " << start_time
           << ", duration: " << duration
           << "\n";
    }
    //
    // range based works
    for (auto node : heap) {
      auto [worker, job, start_time, duration] = node;
      cout << "worker: " << worker
           << ", job: " << job
           << ", start_time: " << start_time
           << ", duration: " << duration
           << "\n";
    }
    //*/
    // range based doesn't work with struct binding
    for (auto &[worker, job, start_time, duration] : heap)
      cout << "worker: " << worker
           << ", job: " << job
           << ", start_time: " << start_time
           << ", duration: " << duration
           << "\n";
    cout << "\n";
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<tuple<long long, long long, long long, long long> > heap(num_workers_);
    // <worker, job, start_time, duration>
    long long heap_size = 0;
    // all jobs assigned workers in order untill all workers are busy
    for (long long i = 0; i < num_workers_ && i < jobs_.size(); i ++) {
      heap[i] = make_tuple(i, i, 0, jobs_[i]);
      heap_size ++;
    }

    // show(heap);
    //organize heap into a heap
    for (long long i = num_workers_ / 2; i >= 0; i --) {
      sift_down(i, heap, heap_size);
    }
    // show(heap);
    //heap(0) end time to be added to the next waiting job and sifted down
    for (long long i = num_workers_; i < jobs_.size(); i ++) {
      // read the first from the heap and save it as finished
      auto [_worker, _job, _start_time, _duration] = heap[0];
      assigned_workers_[_job] = _worker;
      start_times_[_job] = _start_time;
      // add thje next job to the one in the heap of (0);
      heap[0] = make_tuple(_worker, i, _start_time + _duration, jobs_[i]);
      // sift it down to where it belongs
      sift_down(0, heap, heap_size);
    }
    // show(heap);
    // empty the heap and write the results
    while (heap_size > 0) {
      auto [_worker, _job, _start_time, _duration] = heap[0];
      if (_job == -1)
        break;
      assigned_workers_[_job] = _worker;
      start_times_[_job] = _start_time;
      heap[0] = make_tuple(-1, -1, -1, 2e9);
      swap(heap[0], heap[heap_size - 1]);
      heap_size --;
      sift_down(0, heap, heap_size);
    }
    //*/
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
