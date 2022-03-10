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

struct Node* IterativeReverseLinkedList(struct Node* head)
{
    Node* left = NULL; Node* current = head; Node* right = NULL;
    while(current != NULL)
    {
       right = current->next;
       current->next = left;
       left = current;
       current = right;
    }
    current = left;
    return current;
}

int main()
{
    struct Node* head = NULL;
    head = Insert(head, 2);
    head = Insert(head, 4);
    head = Insert(head, 5);
    head = Insert(head, 7);
    
    Print(head);
    head = IterativeReverseLinkedList(head);
    Print(head);
    
    return 0;
}
