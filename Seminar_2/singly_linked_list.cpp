#include <iostream>


struct Node {
   int data;
   Node* next;
};

Node* head = NULL;

void insert(int new_data) {
   Node* new_node = new Node();
   new_node->data = new_data;
   new_node->next = head;
   head = new_node;
}

void display() {
    if (head == NULL)
    {
        std::cout << "The List is empty!" << std::endl;
        return;
    }
    std::cout << "The List is:" << std::endl;
    Node* temp = head;
    while (temp != NULL)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}


void reverse()
{
    std::cout << "Reversing the list!" << std::endl;
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

void destroy() {
    Node* current = head;
    while (current != NULL)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
}

int main() {
   insert(1);
   insert(2);
   insert(3);
   insert(4);
   insert(5);
   
   display();
   reverse();
   display();
   destroy();
   display();
   return 0;
}
