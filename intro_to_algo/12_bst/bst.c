/*
 Author: Kumar Shubham

 Binary search tree practice
  1) Insert
  2) Search
  3) Maximum
  4) Minimum
  5) successor
  6) Predecessor
  7) delete
*/


#include <stdio.h>
#include<stdlib.h>

typedef struct node {
    int key;
    struct node *parent;
    struct node *left;
    struct node *right;
}Node;

struct node *get_node(int val) {
    struct node *tmp = malloc(sizeof(struct node));
    tmp->key = val;
    tmp->parent = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}


struct node *bst_insert(Node *root, int val) {
    struct node *tmp = get_node(val);
    if(root == NULL) {
        root = tmp;
    }
    else {
        struct node *cur = root;
        struct node *prev = NULL;
        while(cur != NULL) {
            if(cur->key == val){
                printf("\nkey %i already present\n", cur->key);
                return root;
            }
            prev = cur;
            if(val > cur->key) {
                cur = cur->right;
            }
            else {
                cur = cur->left;
            }
        }

        if(val > prev->key) {
            prev->right = tmp;
        }
        else {
            prev->left = tmp;
        }

        tmp->parent = prev;
    }

    return root;
}


struct node *bst_search(Node *root, int val) {
    if(root == NULL || root->key == val){
        return root;
    }
    else if(val > root->key){
        bst_search(root->right, val);
    }
    else {
        bst_search(root->left, val);
    }
}

struct node *bst_minimum(Node *root){
    while(root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct node *bst_maximum(Node *root){
    while(root->right != NULL) {
        root = root->right;
    }
    return root;
}

struct node *successor(Node *k) {

    // if left child is not null , get the minimum from the right sub-tree.
    if(k->right != NULL) {
         return bst_minimum(k->right);
    }

    // the first ancestor of the node that is a left child of its parent.
    struct node *p;
    while(k->parent != NULL){
        p = k->parent;
        if(p->left == k){
            break;
        }
        k = p;
    }
    return p;
}

void transplant(Node *root, Node *u, Node *v){
    if(u->parent == NULL){
        root = v;
    }

    if(u == u->parent->left){
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }

    if(v !=NULL){
        v->parent = u->parent;
    }
}

void bst_delete(Node *root, int val) {
    struct node *z = bst_search(root, val);
    if(z == NULL){
        return;
    }
    printf("Deleting node with value %i\n", val);
    if(z->left == NULL){
        transplant(root, z, z->right);
    }
    else if(z->right == NULL) {
        transplant(root, z, z->left);
    }
    else {
        struct node *y = bst_minimum(z->right);
        if(y->parent != z){
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void inorder(struct node *tmp) {
    if(tmp != NULL) {
        inorder(tmp->left);
        printf("%i ", tmp->key);
        inorder(tmp->right);
    }
}

int main(int argc, char *argv[]) {

    int arr[] = {50, 30 ,20, 40, 70, 60, 80, 80, 90};
    int i, n = sizeof(arr)/sizeof(arr[0]);
    struct node *root = NULL;

    printf("inserting values: ");
    for(i=0;i<n;i++) {
        printf("%i%c", arr[i], (i<n-1)?' ': '\n');
        root = bst_insert(root, arr[i]);
    }

    printf("inorder walk: ");
    inorder(root);
    printf("\n");
    
    struct node *x;
    int val = 40;
    x = bst_search(root, val);
    if(x != NULL) {
        printf("%i key found\n", x->key);
    }
    else {
        printf("key not found");
    }

    struct node *min = NULL, *max = NULL;
    min = bst_minimum(root);
    printf("bst minimum: %i\n", min->key);

    max = bst_maximum(root);
    printf("bst maximum: %i\n", max->key);


    bst_delete(root, 40);
    printf("inorder walk: ");
    inorder(root);
    printf("\n");

    return 0;

}