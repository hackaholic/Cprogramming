#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

struct Student {
    char *name;
    int age;
};

struct Node {
    struct Student *student;
    struct Node *next;
};

struct Node *hashtable[HASH_SIZE];

void addNode(struct Node *node, const int hash_value) {
    if(hashtable[hash_value] == NULL) {
        hashtable[hash_value] = node;
        return;
    }
    struct Node *cur = hashtable[hash_value];
    struct Node *prev = NULL;
    while(cur != NULL) {
        if (strcmp(cur->student->name, node->student->name) == 0) {
            printf("%s already present, Updating ...\n", node->student->name);
            if(prev == NULL) {

                hashtable[hash_value] = node;
                node->next = cur->next;
                free(cur);
                return;
            }
            prev->next = node;
            node->next = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    prev->next = node;
}


unsigned int hashone(const char *name) {

    // return strlen(name) % hash_size ;  // this will result in collision
    const char *temp_name = name;
    unsigned int hash_value = 0;
    while(*temp_name != '\0') {
        hash_value += (*temp_name - '0');
        temp_name++;
    }
    //printf("Hash vale: %s -> %i\n", name, hash_value);
    return hash_value % HASH_SIZE;

}

struct Node *hashlookup(char *name) {
    unsigned int hash_value;
    struct Node *tmp_student = (struct Node*) malloc(sizeof(struct Node));
    printf("Inside hashlookup\n");
    hash_value = hashone(name);
    printf("hashlookup: %i\n", hash_value);
    printf("%s\n", hashtable[hash_value]->student->name);
    tmp_student = hashtable[hash_value];
    if (tmp_student == NULL) {
        return NULL;
    }
    while(tmp_student != NULL) {
        printf("hashlookup: %s\n", tmp_student->student->name);
        if(strcmp(tmp_student->student->name, name) == 0) {
            printf("ok\n");
            return tmp_student;
        }
        tmp_student = tmp_student->next;
    }
}

void print_hashtable() {
    int i;
    struct Node *temp;
    for(i=0;i<HASH_SIZE;i++) {
        if(hashtable[i] != NULL) {
            temp = hashtable[i];
            while(temp != NULL) {
                printf("%i -> name: %s\n", i, temp->student->name);
                temp = temp->next;
            }
        }
    }
}

int main() {
    printf("Practice Hashtable\n");

    printf("Coco -> %i\n", hashone("Coco"));
    printf("Bob -> %i\n", hashone("Bob"));
    printf("Shiro -> %i\n", hashone("Shiro"));
    printf("Alice -> %i\n", hashone("Alice"));
    printf("Mini -> %i\n", hashone("Mini"));
    printf("Batman -> %i\n", hashone("Batman"));
    printf("DStrange -> %i\n", hashone("DStrange"));
    printf("Bill -> %i\n", hashone("Bill"));
    printf("Ron -> %i\n", hashone("Ron"));
    printf("Anu -> %i\n", hashone("Anu"));

    char *name[10] = {"Coco", "Anu", "Shiro", "Alice", "Mini", "Batman", "DStrange", "Bill", "Ron", "Anu"};
    int age[10] = {2, 5, 8, 3, 9, 12, 15, 11, 10, 1};
    int i, hash_value;
    for(i=0;i<10;i++) {
        struct Student *stu_ptr = (struct Student*) malloc(sizeof(struct Student));
        struct Node *node_ptr = (struct Node*) malloc(sizeof(struct Node));
        stu_ptr->name = name[i];
        stu_ptr->age = age[i];
        node_ptr->next = NULL;
        node_ptr->student = stu_ptr;
        hash_value = hashone(node_ptr->student->name);
        // printf("%s -> %i\n", name[i], hash_value);
        //hashtable[hash_value] = node_ptr;
        addNode(node_ptr, hash_value);
    }

    print_hashtable();
    struct Node *tmp;
    tmp = hashlookup("Anu");
    //printf("ok: name->%s: age->%i", tmp->student->name, tmp->student->age);


    
}