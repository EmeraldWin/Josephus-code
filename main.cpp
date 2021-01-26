#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(string payload) {
    Node* person = new Node;
    person->payload = payload;
    person->next = nullptr;
   
    return person;
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        if (head == nullptr) {
            head = newNode(name); 
            prev = head;
        } else {
            prev->next = newNode(name);
            prev = prev->next; 
        }
    }

    if (prev != nullptr) { 
        prev->next = head;
    }
    return head;
}

void print(Node* start) { 
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) {
            break; 
        }
    }
}

Node* runGame(Node* start, int k) { 
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { 
        for (int i = 0; i < k; ++i) { 
            prev = curr;
            curr = curr->next;
        }

        prev->next = curr->next;
        delete curr;
        curr = prev; 
        prev = prev->next;
        curr = curr->next;
    }

    return curr; 
}


int main() {
    int n=1, k=1, max; 
    string name;
    vector<string> names;

    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}
