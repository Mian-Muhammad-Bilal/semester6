#include <iostream>
using namespace std;

class D_LinkedList
{
private:
    class Node
    {
    public:
        int data;
        Node *next;
        Node *prev;
        Node(int data)
        {
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };

    Node *head;

public:
    D_LinkedList()
    {
        head = nullptr;
    }

    void InsertAtBegin(int d)
    {
        Node *newNode = new Node(d);
        if (head != nullptr)
        {
            newNode->next = head;
            head->prev = newNode;
        }
        head = newNode;
    }

    void InsertAtEnd(int d)
    {
        Node *newNode = new Node(d);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    void InsertAfter(int f, int d)
    {
        Node *temp = head;
        while (temp != nullptr && temp->data != f)
        {
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            cout << "Node with data " << f << " not found." << endl;
            return;
        }
        Node *newNode = new Node(d);
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next != nullptr)
        {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }

    void InsertBefore(int f, int d)
    {
        Node *temp = head;
        while (temp != nullptr && temp->data != f)
        {
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            cout << "Node with data " << f << " not found." << endl;
            return;
        }
        Node *newNode = new Node(d);
        newNode->prev = temp->prev;
        newNode->next = temp;
        if (temp->prev != nullptr)
        {
            temp->prev->next = newNode;
        }
        else
        {
            head = newNode;
        }
        temp->prev = newNode;
    }

    void DeleteFromBegin()
    {
        if (head == nullptr)
        {
            cout << "List is already empty." << endl;
            return;
        }
        Node *temp = head;
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        delete temp;
    }

    void DeleteFromEnd()
    {
        if (head == nullptr)
        {
            cout << "List is already empty." << endl;
            return;
        }
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        if (temp->prev != nullptr)
        {
            temp->prev->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        delete temp;
    }

    void DeleteList()
    {
        while (head != nullptr)
        {
            DeleteFromBegin();
        }
    }

    void Display()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "null" << endl;
    }
};

int main()
{
    D_LinkedList l;
    cout << "After InsertAtBegin" << endl;
    l.InsertAtBegin(5);
    l.InsertAtBegin(4);
    l.InsertAtBegin(3);
    l.InsertAtBegin(2);
    l.InsertAtBegin(1);
    l.Display();

    cout << "\nAfter InsertAtEnd" << endl;
    l.InsertAtEnd(6);
    l.InsertAtEnd(7);
    l.Display();

    cout << "\nAfter InsertAfter" << endl;
    l.InsertAfter(3, 999);
    l.Display();

    cout << "\nAfter InsertBefore" << endl;
    l.InsertBefore(3, 111);
    l.Display();

    cout << "\nAfter DeleteFromBegin" << endl;
    l.DeleteFromBegin();
    l.Display();

    cout << "\nAfter DeleteFromEnd" << endl;
    l.DeleteFromEnd();
    l.Display();

    cout << "\nAfter DeleteList" << endl;
    l.DeleteList();
    l.Display();

    return 0;
}
