#include <iostream>
#include <vector>
#include <string>

using namespace std;
using std::vector;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

class Node {
public:
    int number;
    string name;
    Node* next;
    Node(int number, string name) {
        this -> number = number;
        this -> name = name;
        this -> next = NULL;
    }
};

class LinkedList {
    Node* head;
public:
    LinkedList() {
        head = NULL;
    }

    void insertNode(int number, string name) {
        Node *node = new Node(number, name);
        node -> next = head;
        head = node;
    }

    string findNode(int phone) {
        Node *node = head;
        string name = "not found";
        while (node != NULL) {
            if (node -> number == phone)
                break;
            node = node -> next;
        }
        if (node != NULL)
            name = node -> name;
        return name;
    }

    void deleteNode(int phone)
    {
        if (head == NULL) {
            //cout << "List empty." << endl;
            return;
        }
        Node* node = head;
        if (node -> next == NULL){
            if (node -> number == phone) {
                head = NULL;
                delete node;
            }
        } else {
            // previous will be null if the node is head node
            Node* previous = NULL;
            while (node != NULL) {
                if (node -> number == phone) {
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

class HashMap {
    int p, a, b, card;
    vector<LinkedList> phone;

public:
    HashMap (int p = 10000019, int a = 34, int b = 2, int card = 1000):
        p(p), a(a), b(b), card(card), phone(card) {
    }

    int hash(int _phone) {
        // perform hash function to get index to write or read
        int index = 0;
        index = (_phone * a + b) % p;
        index %= card;
        return index;
    }

    void insert (int number, string name) {
        phone[hash(number)].insertNode(number, name);
    }

    void deletePhone (int number) {
        phone[hash(number)].deleteNode(number);
    }

    string find (int number) {
        return phone[hash(number)].findNode(number);
    }
};

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    HashMap phoneBook;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add")
            phoneBook.insert(queries[i].number, queries[i].name);
        else if (queries[i].type == "del")
            phoneBook.deletePhone(queries[i].number);
        else
            result.push_back(phoneBook.find(queries[i].number));
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
