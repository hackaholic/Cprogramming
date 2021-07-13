#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

struct node *addNode(struct node *head, int val) {
    struct node *temp = (struct node*) malloc(sizeof(struct node));
    struct node *cur = head;
    temp->val = val;
    temp->next = NULL;
    if (head == NULL) {
        return temp;
    }
    while (cur->next != NULL ){
        cur = cur->next;
    }
    cur->next = temp;
    return head;
}

void displayNode(struct node *head) {
    if (head == NULL) {
        printf("Empty Linked List");
    }
    while (head != NULL) {
        printf("node:%p, %i\n", head, head->val);
        head = head->next;
    }
}

int main() {
     // will create linked list from array element
     int i;
     int arr[7] = {1, 2, 3, 4, 5, 6, 7};
     struct node *head = NULL;
     for(i=0; i < sizeof(arr)/sizeof(int); i++){
         printf("adding node: %i\n", arr[i]);
         head = addNode(head, arr[i]);
     }
     displayNode(head);
}