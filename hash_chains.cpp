#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class Node {
public:
    string word;
    Node* next;
    Node(string word) {
        this -> word = word;
        this -> next = NULL;
    }
};

class LinkedList {
    Node* head;
public:
    LinkedList() {
        head = NULL;
    }

    string print() {
        Node *node = head;
        if (node == NULL)
            return "\n";
        string res = "";
        while (node -> next != NULL) {
            //print node
            res += node -> word + " ";
            node = node -> next;
        }
        res += node -> word + "\n";
        return res;
    }

    void insertNode(string word) {
        // we check the list and if its not in there we add it at the front
        for (Node *node = head; node != NULL; node = node -> next)
            if (node -> word == word)
                return;
        Node *node = new Node(word);
        node -> next = head;
        head = node;
    }

    string findNode(string word) {
        Node *node = head;
        string res = "no\n";
        while (node != NULL) {
            if (node -> word == word)
                break;
            node = node -> next;
        }
        if (node != NULL)
            res = "yes\n";
        return res;
    }

    void deleteNode(string word)
    {
        if (head == NULL) {
            //cout << "List empty." << endl;
            return;
        }
        Node* node = head;
        if (node -> next == NULL){
            if (node -> word == word) {
                head = NULL;
                delete node;
            }
        } else {
            // previous will be null if the node is head node
            Node* previous = NULL;
            while (node != NULL) {
                if (node -> word == word) {
                    // we delete
                    if (previous == NULL && node == head) {
                        head = node -> next;
                        delete node;
                        if (head == NULL)
                            break;
                        node = head;
                    } else {
                        previous -> next = node -> next;
                        delete node;
                        if (previous == NULL)
                            break;
                        node = previous -> next;
                    }
                } else {
                    previous = node;
                    node = node -> next;
                }
            }
        }
    }
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<LinkedList> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count):
        bucket_count(bucket_count),
        elems(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void processQuery(const Query& query) {
        if (query.type == "check")
            cout << elems[query.ind].print();
        else if (query.type == "find")
            cout << elems[hash_func(query.s)].findNode(query.s);
        else if (query.type == "add")
            elems[hash_func(query.s)].insertNode(query.s);
        else if (query.type == "del")
            elems[hash_func(query.s)].deleteNode(query.s);
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
