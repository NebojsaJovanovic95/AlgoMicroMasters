#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>

using std::string;
using std::vector;
using std::swap;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::get;
using std::sort;
using std::max;
using std::queue;

struct customer {
    int customer_id;
    float arrival, service;
};

bool cmp(customer a, customer b) {
    if (a.arrival < b.arrival)
        return true;
    else if (a.arrival - b.arrival <= 1e-6) {
        return a.service < b.service;
    } else return false;
}

struct customer_log {
    int customer_id;
    float arrival, begin, end, t_service, t_queue, t_system;
};

struct and_log {
    int event;
    float time;
    string type;
    int customer_id;
    string server;
    int in_q;
    int in_sys;
};

struct kpi {
    struct {
        float time_in_queue;
        float time_in_sys;
        float num_in_queue;
        float num_in_sys;
        float server_utilization;
    } average, maximum;
};

customer get_data(const string &line) {
    int len = line.size();
    int commas[2];
    int com = 0;
    for (size_t i = 0; i < len; i ++) {
        if (line[i] == ',')
            commas[com ++] = i;
    }
    customer customer;
    customer.customer_id = stoi(line.substr(0, commas[0]));
    customer.arrival = stof(line.substr(commas[0] + 1, commas[1]));
    customer.service = stof(line.substr(commas[1] + 1, len));
    /*std::cout << "Customer: " << customer
              << ", Arrival: " << arrival
              << ", Service: " << service
              << "\n";*/
    return customer;
}

vector<customer> read_csv(const string &in_csv) {
    ifstream fin (in_csv);
    vector<customer> input;
    string line_in;
    size_t row = 0;
    while (getline(fin, line_in)) {
        if (row >= 2) {
            //its real input
            input.push_back(get_data(line_in));
        }
        row ++;
    }
    fin.close();
    return input;
}

customer_log new_buffer(float last_end) {
    customer_log new_log;
    new_log.customer_id = 0;
    new_log.arrival = 0;
    new_log.begin = 0;
    new_log.end = last_end;
    new_log.t_service = 0;
    new_log.t_queue = 0;
    new_log.t_system = 0;
    return new_log;
}

customer_log new_customer_log(customer new_customer, customer_log buffer) {
    customer_log new_log = buffer;
    float zero = 0;
    new_log.customer_id = new_customer.customer_id;
    new_log.arrival = new_customer.arrival;
    new_log.begin = max(buffer.end, new_customer.arrival);
    new_log.end = new_log.begin + new_customer.service;
    new_log.t_service = new_customer.service;
    new_log.t_queue = max(zero, new_log.begin - new_customer.arrival);
    new_log.t_system = max(zero, new_log.end - new_customer.arrival);
    return new_log;
}

and_log new_arrival(customer_log item_log, customer item, int index, int in_q) {
    and_log new_log;
    new_log.event = index;
    new_log.time = item.arrival;
    new_log.type = "Arrival";
    new_log.customer_id = item_log.customer_id;
    if (item.arrival > item_log.end) {
        new_log.server = "idle";
        new_log.in_sys = 0;
    } else {
        new_log.server = "Busy";
        new_log.in_sys = 1;
    }
    new_log.in_q = in_q;
    return new_log;
}

and_log new_departure(customer_log item_log, customer item, int index, int in_q) {
    and_log new_log;
    new_log.event = index;
    new_log.time = item_log.end;
    new_log.type = "Departure";
    new_log.customer_id = item_log.customer_id;
    if (item.arrival > item_log.end) {
        new_log.server = "idle";
        new_log.in_sys = 0;
    } else {
        new_log.server = "Busy";
        new_log.in_sys = 1;
    }
    new_log.in_q = in_q;
    return new_log;
}

// implementation with a single buffer
vector<customer_log> process_customers(vector<customer> &input, vector<and_log> &and_log_output) {
    vector<customer_log> customer_log_output(input.size());
    queue<customer_log> buffer_q;
    float last_end = 0; // end of the last process in the queue
    customer_log buffer = new_buffer(last_end);
    int and_log_index = 1;
    buffer = new_customer_log(input[0], buffer);
    and_log_output.push_back(
        new_arrival(
            buffer,
            input[0],
            and_log_index ++,
            0
            ));
    buffer_q.push(buffer);
    last_end = buffer.end;
    //initiallize the buffer to take in the first arrived customer
    for (size_t i = 1; i < input.size(); i ++) {
        // log the customer in buffer
        while (!buffer_q.empty() && input[i].arrival > buffer_q.front().end) {
            // we pop from the q and process departure
            buffer = buffer_q.front();
            buffer_q.pop();
            customer_log_output[buffer.customer_id - 1] = buffer;
            and_log_output.push_back(
                new_departure(
                    buffer,
                    input[buffer.customer_id - 1],
                    and_log_index ++,
                    buffer_q.size() - 1
                    ));
            // we send q size - 1 because the currently operated one is still q.front()
        }
        // we have to check if the queue is not empty make buffer the front of the q
        if (!buffer_q.empty())
            buffer = new_buffer(last_end);
        else
            buffer = new_buffer(0);
        buffer = new_customer_log(input[i], buffer);
        buffer_q.push(buffer);
        last_end += input[i].service;
        buffer = new_customer_log(input[i], buffer);
        and_log_output.push_back(
            new_arrival(
                buffer,
                input[i],
                and_log_index ++,
                buffer_q.size() - 1
                ));
        // we send q size - 1 because the currently operated one is still q.front()
    }
    while (!buffer_q.empty()) {
        buffer = buffer_q.front();
        buffer_q.pop();
        customer_log_output[buffer.customer_id - 1] = buffer;
        and_log_output.push_back(
            new_departure(
                buffer,
                input[buffer.customer_id - 1],
                and_log_index ++,
                buffer_q.size()
                ));
    }


    return customer_log_output;
}

kpi new_kpi () {
    float zero = 0;
    kpi result;
    result.maximum.time_in_queue = zero;
    result.maximum.time_in_sys = zero;
    result.maximum.num_in_queue = zero;
    result.maximum.num_in_sys = zero;
    result.maximum.server_utilization = zero;
    result.average.time_in_queue = zero;
    result.average.time_in_sys = zero;
    result.average.num_in_queue = zero;
    result.average.num_in_sys = zero;
    result.average.server_utilization = zero;
    return result;
}

kpi compute_kpi(vector<customer_log> &customer_log_output, vector<and_log> &and_log_output) {
    kpi result = new_kpi();
    for (auto &[customer_id, arrival, begin, end, t_service, t_queue, t_system] : customer_log_output) {
        result.maximum.time_in_queue = max(result.maximum.time_in_queue, t_queue);
        result.maximum.time_in_sys = max(result.maximum.time_in_sys, t_system);
        //result.maximum.num_in_queue = zero;
        //result.maximum.num_in_sys = zero;
        //result.maximum.server_utilization = zero;
        result.average.time_in_queue += t_queue;
        result.average.time_in_sys += t_system;
        //result.average.num_in_queue = zero;
        //result.average.num_in_sys = zero;
        //result.average.server_utilization = zero;
    }
    result.average.time_in_queue /= customer_log_output.size();
    result.average.time_in_sys /= customer_log_output.size();
    float prev_time = 0;
    float prev_in_sys = 0;
    for (auto &[event, time, type, customer_id, server, in_q, in_sys] : and_log_output) {
        //result.maximum.time_in_queue = max(result.maximum.time_in_queue, t_queue);
        //result.maximum.time_in_sys = max(result.maximum.time_in_sys, t_system);
        result.maximum.num_in_queue = max(result.maximum.num_in_queue, (float) in_q);
        result.maximum.num_in_sys = max(result.maximum.num_in_sys, (float) in_sys);
        result.maximum.server_utilization += prev_in_sys * (time - prev_time);
        //result.average.time_in_queue += t_queue;
        //result.average.time_in_sys += t_system;
        result.average.num_in_queue += in_q;
        result.average.num_in_sys += in_sys;
        result.average.server_utilization += prev_in_sys * (time - prev_time);
        prev_time = time;
        prev_in_sys = in_sys;
    }
    result.average.num_in_queue /= and_log_output.size();
    result.average.num_in_sys /= and_log_output.size();
    result.average.server_utilization /= prev_time;
    // now we have all the kpis computed
    return result;
}

void print_customers(vector<customer> &customers) {
    for (auto &[customer_id, arrival, service] : customers)
        std::cout << "Customer: " << customer_id
                  << ", Arrival: " << arrival
                  << ", Service: " << service
                  << "\n";
}

void print_customer_log(vector<customer_log> &log) {
    for (auto &[customer_id, arrival, begin, end, t_service, t_queue, t_system] : log) {
        std::cout << customer_id << ", "
                  << arrival << ", "
                  << begin << ", "
                  << end << ", "
                  << t_service << ", "
                  << t_queue << ", "
                  << t_system << "\n";
    }
}

void print_and_log(vector<and_log> &log) {
    for (auto &[event, time, type, customer_id, server, in_q, in_sys] : log)
        std::cout << event << ", "
             << time << ", "
             << type << ", "
             << customer_id << ", "
             << server << ", "
             << in_q << ", "
             << in_sys << "\n";
}

void print_kpi(kpi log) {
    std::cout  << log.maximum.time_in_queue << " "
          << log.maximum.time_in_sys << " "
          << log.maximum.num_in_queue << " "
          << log.maximum.num_in_sys << " "
          << log.maximum.server_utilization << "\n"
          << log.average.time_in_queue << " "
          << log.average.time_in_sys << " "
          << log.average.num_in_queue << " "
          << log.average.num_in_sys << " "
          << log.average.server_utilization << "\n";
}

void print_customer_log_csv(vector<customer_log> &log, const string &out_csv) {
    ofstream fout;
    fout.open(out_csv);
    fout << " , Timestamp [min], , , Duration [min], , \n";
    fout<< "Customer Number, Arrival, Begin Service, End Service, Time in Service, Time in Queue, Time in System\n";
    for (auto &[customer_id, arrival, begin, end, t_service, t_queue, t_system] : log) {
        fout << customer_id << ", "
                  << arrival << ", "
                  << begin << ", "
                  << end << ", "
                  << t_service << ", "
                  << t_queue << ", "
                  << t_system << "\n";
    }
    fout.close();
}

void print_and_log_csv(vector<and_log> &log, const string &out_csv) {
    ofstream fout;
    fout.open(out_csv);
    fout << "Event, , , , System Status, , \n";
    fout << "Event #, Time, Type, Customer #, Server, # in Queue, # in System\n";
    for (auto &[event, time, type, customer_id, server, in_q, in_sys] : log)
        fout << event << ", "
             << time << ", "
             << type << ", "
             << customer_id << ", "
             << server << ", "
             << in_q << ", "
             << in_sys << "\n";
    fout.close();
}

void print_kpi_csv(kpi log, const string &out_csv) {
    ofstream fout;
    fout.open(out_csv);
    fout << " , Customer Time [min], , Customer Volume [#], \n";
    fout << "Statistic, In Queue, In System, In Queue, In System, Server Utilization\n";
    fout << "Maximum, "
         << log.maximum.time_in_queue << ", "
         << log.maximum.time_in_sys << ", "
         << log.maximum.num_in_queue << ", "
         << log.maximum.num_in_sys << ", "
         << log.maximum.server_utilization << "\n"
         << "Average, "
         << log.average.time_in_queue << ", "
         << log.average.time_in_sys << ", "
         << log.average.num_in_queue << ", "
         << log.average.num_in_sys << ", "
         << log.average.server_utilization << "\n";
    fout.close();
}

int main(int argc, char * argv[]) {
    string input_csv = "input.csv";
    string customer_log_csv = "customer_log.csv";
    string and_log_csv = "and_log.csv";
    string kpi_csv = "kpi.csv";
    if (argc != 1) {
        if (argc >= 2)
            input_csv = argv[1];
        if (argc >= 3)
            customer_log_csv = argv[2];
        if (argc >= 4)
            and_log_csv = argv[3];
        if (argc >= 5)
            kpi_csv = argv[4];
    }

    vector<customer> input = read_csv(input_csv);
    std::sort(input.begin(), input.end(), cmp);
    // print_customers(input);
    // the input is now sorted
    vector<and_log> and_log_output;
    vector<customer_log> customer_log_output = process_customers(input, and_log_output);
    // print_customer_log(customer_log_output);
    // print_and_log(and_log_output);
    // now we have our logs, we compute our statistics
    // print_kpi(compute_kpi(customer_log_output, and_log_output));
    // print it all in a file
    print_customer_log_csv(customer_log_output, customer_log_csv);
    print_and_log_csv(and_log_output, and_log_csv);
    // now we have our logs, we compute our statistics
    print_kpi_csv(compute_kpi(customer_log_output, and_log_output), kpi_csv);
}