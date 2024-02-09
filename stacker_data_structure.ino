
struct Node {
    int8_t data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void insert(int8_t value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    // Additional methods (e.g., delete, search, etc.) can be added as per your requirements.
};

int main() {
    DoublyLinkedList myList;

    myList.insert(10);
    myList.insert(20);
    myList.insert(30);


    return 0;
}
