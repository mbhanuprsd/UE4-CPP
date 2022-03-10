#include <iostream>

using namespace std;

struct Node {
    int data;
    struct Node* next;
};

struct Node* Insert(Node* head, int data)
{
    Node* temp = (struct Node*) malloc(sizeof(struct Node*));
    temp->data = data;
    temp->next = NULL;
    
    if (head == NULL) head = temp;
    else{
        Node* temp1 = head;
        while(temp1->next != NULL) temp1 = temp1->next;
        temp1->next = temp;
    }
    return head;
}

void Print(struct Node* p)
{
    if (p == NULL) return;
    cout<<p->data<<endl;
    Print(p->next);
}

void ReversePrint(struct Node* p)
{
    if (p == NULL) return;
    ReversePrint(p->next);
    cout<<p->data<<endl;
}

struct Node* IterativeReverse(struct Node* head)
{
    Node* prev = NULL; Node* current = head; Node* next = NULL;
    while(current != NULL)
    {
       next = current->next;
       current->next = prev;
       prev = current;
       current = next;
    }
    return prev;
}

struct Node* RecursiveReverse(struct Node* p)
{
    if (p== NULL || p->next == NULL)
    {
        return p;
    }
    Node* reversedHead = RecursiveReverse(p->next);
    p->next->next = p;
    p->next = NULL;
    return reversedHead;
}

int main()
{
    struct Node* head = NULL;
    head = Insert(head, 2);
    head = Insert(head, 4);
    head = Insert(head, 5);
    head = Insert(head, 7);
    
    Print(head);
    head = RecursiveReverse(head);
    Print(head);
    
    return 0;
}
