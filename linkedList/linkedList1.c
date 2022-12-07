#include<stdio.h>
#include<stdlib.h>

struct node {
    int val;
    struct node *next;
};

struct node *addNode(struct node *head, int val) {
    struct node *temp = malloc(sizeof(struct node));
    temp->val = val;
    temp->next = NULL;
    if(head == NULL) {  
        head = temp;
        return head;
    }
    struct node *cur = head;
    while(cur->next != NULL)
        cur = cur->next;
    cur->next = temp;
    return head;
}

void displayNode(struct node *head) {
    struct node *temp;
    temp = head;
    if(head == NULL) {
        printf("linklist is empty\n");
    }
    else {
        while(temp != NULL) {
            printf("val: %i\n", temp->val);
            temp = temp->next;
        }
    }
}

struct node *reverse(struct node *head) {
    if(head ==  NULL) {
        printf("list is empty\n");
        return NULL;
    }
    if(head->next == NULL) {
        return head;
    }
    struct node *prev = NULL;
    struct node *cur = NULL;
    struct node *next = NULL;
    cur = head;
    while(cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
    return head;
}

int main(int argc, char *argv[]) {
    int n,i,val;
    struct node *head = NULL;
    printf("enter no of nodes n: ");
    scanf("%i", &n);
    printf("Enter elements\n");
    for(i=0;i<n;i++){
        scanf("%i", &val);
        head = addNode(head, val);
    }
    displayNode(head);
    head = reverse(head);
    printf("Reversed Linked list\n");
    displayNode(head);
    return 0;
}