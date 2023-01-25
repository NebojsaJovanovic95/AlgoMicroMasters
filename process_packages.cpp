#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        // write your code here
        Response response(true, request.arrival_time);
        if (finish_time_.size() == 0) {
            // we add it on the queue and it keeps its arrival time as start time
            finish_time_.push(request.arrival_time + request.process_time);
            response.dropped = false;
        } else if (finish_time_.size() == size_) {
            // check if the top one is done
            if (finish_time_.front() <= request.arrival_time) {
                // response start time will be the finish time of the last item in queue
                response.start_time = std::max(finish_time_.back(), response.start_time);
                response.dropped = false;
                finish_time_.pop();
                finish_time_.push(response.start_time + request.process_time);
            } else {
                // drop the request
                response.start_time = -1;
            }
        } else if (finish_time_.size() < size_) {
            // check if the top one is done
            if (finish_time_.front() <= request.arrival_time) {
                // response start time will be the finish time of the last item in queue
                response.start_time = std::max(finish_time_.back(), response.start_time);
                response.dropped = false;
                finish_time_.pop();
                finish_time_.push(response.start_time + request.process_time);
            } else {
                // we can add it, its start time is the finish time of last item in queue
                response.start_time = std::max(finish_time_.back(), response.start_time);
                response.dropped = false;
                finish_time_.push(finish_time_.back() + request.process_time);
            }
        }
        return response;
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
