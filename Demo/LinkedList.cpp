/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

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
    Print(p->next);
    cout<<p->data<<endl;
}

int main()
{
    struct Node* head = NULL;
    head = Insert(head, 2);
    head = Insert(head, 4);
    head = Insert(head, 5);
    head = Insert(head, 7);
    
    Print(head);
    
    return 0;
}
