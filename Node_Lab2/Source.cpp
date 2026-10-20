#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

bool isEmpty(Node* head)
{
    return head == nullptr;
}

int getLength(Node* head)
{
    if (isEmpty(head))
    {
        return 0;
    }

    int count = 0;
    Node* current = head;
    do
    {
        count++;
        current = current->next;
    } while (current != head);

    return count;
}

void addToHead(Node*& head, int value)
{
    Node* newNode = new Node{ value, nullptr };

    if (isEmpty(head))
    {
        newNode->next = newNode;
        head = newNode;
        return;
    }

    Node* tail = head;
    while (tail->next != head)
    {
        tail = tail->next;
    }

    newNode->next = head;
    tail->next = newNode;
    head = newNode;
}

void addToTail(Node*& head, int value)
{
    Node* newNode = new Node{ value, nullptr };

    if (isEmpty(head))
    {
        newNode->next = newNode;
        head = newNode;
        return;
    }

    Node* tail = head;
    while (tail->next != head)
    {
        tail = tail->next;
    }

    tail->next = newNode;
    newNode->next = head;
}

void printList(Node* head)
{
    if (isEmpty(head))
    {
        cout << "[empty]";
        return;
    }

    Node* current = head;
    do
    {
        cout << current->data;
        current = current->next;
        if (current != head)
        {
            cout << " -> ";
        }
    } while (current != head);
    cout << " -> (loops back to head: " << head->data << ")";
}

void freeList(Node*& head)
{
    if (isEmpty(head))
    {
        return;
    }

    Node* current = head;
    Node* nextNode = nullptr;

    Node* tail = head;
    while (tail->next != head)
    {
        tail = tail->next;
    }
    tail->next = nullptr;

    while (current != nullptr)
    {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

void taskA_deleteSecond(Node*& head)
{
    if (isEmpty(head) || head->next == head)
    {
        return;
    }
    Node* second = head->next;
    head->next = second->next;
    delete second;
}


void taskB_moveLastToHead(Node*& head)
{
    if (isEmpty(head) || head->next == head)
    {
        return;
    }

    Node* prev = nullptr;
    Node* tail = head;

    while (tail->next != head)
    {
        prev = tail;
        tail = tail->next;
    }

    head = tail;
}

void taskC_reverse(Node*& head)
{
    if (isEmpty(head) || head->next == head)
    {
        return;
    }

    Node* prev = nullptr;
    Node* current = head;
    Node* nextNode = nullptr;

    Node* tail = head;
    while (tail->next != head)
    {
        tail = tail->next;
    }

    do
    {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    } while (current != head);

    head->next = prev;
    head = prev;
}

void showState(const char* stepName, Node* head)
{
    cout << stepName << endl;
    cout << "List contain: ";
    printList(head);
    cout << "\nList length: " << getLength(head) << "\n\n";
}

int main()
{
    Node* L = nullptr;

    addToTail(L, 20);
    addToTail(L, 30);
    addToTail(L, 40);
    addToHead(L, 10);
    addToTail(L, 50);

    showState("Initial state of list L:", L);

    taskA_deleteSecond(L);
    showState("After Task A (Delete second element):", L);

    taskB_moveLastToHead(L);
    showState("After Task B (Move last element to head):", L);

    taskC_reverse(L);
    showState("After Task C (Reverse list by rearranging pointers):", L);

    /*cout << "================================ POINTER TRANSITION TABLE ================================" << endl;
    cout << "Task   | Nodes Before Operation  | Key Pointer Mutation                            | Result" << endl;
    cout << "-------+-------------------------+-------------------------------------------------+-------------------------" << endl;
    cout << "Task A | [10]->[20]->[30]->[40]  | head->next = (head->next)->next; delete [20];   | [10]->[30]->[40]->[50]" << endl;
    cout << "Task B | [10]->[30]->[40]->[50]  | head = tail; (where tail->next already == head) | [50]->[10]->[30]->[40]" << endl;
    cout << "Task C | [50]->[10]->[30]->[40]  | curr->next = prev (in loop); head = prev;       | [40]->[30]->[10]->[50]" << endl;
    cout << "==========================================================================================" << endl;*/

    freeList(L);
    return 0;
}