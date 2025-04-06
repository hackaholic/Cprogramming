#include <stdio.h>

int main(int argc, char *argv[]) {

    // 1. Declaring a Structure
    struct pet {
        char *name;
        int age;
    };

    // 2. Declaring Variables of Structure
    struct pet mypet;

    // 3. Accessing Members Using Dot . Operator
    mypet.name = "Mini";
    mypet.age = 8;

    printf("Mypet: name: %s, age: %i\n", mypet.name, mypet.age);

    // 4. Using Pointer to Structure
    struct pet *p = &mypet;
    
    // Access using -> operator:
    printf("Mypet: name: %s, age: %i\n", p->name, p->age);

    // 5. Array of Structures

    struct pet cats[]  = {
        {"coco", 7},
        {"mini", 8},
        {"dora", 7},
        {"oreo", 6},
        {"shiro", 6}
    };

    for(int i=0;i<5;i++) {
        printf("%s is %d\n", cats[i].name, cats[i].age);
    }

    // 6. Using typedef for Simpler Syntax
    typedef struct animal {
        char *name;
        int age;
    } Animal;

    Animal an;
    an.name = "Tiger";
    an.age = 10;

    typedef struct pet Pet;

    Pet pets[3] = {
        {"Nova", 4},
        {"Shiro", 6},
        {"Suri", 2}
    };
    
    Pet *p1 = pets;
    printf("First cat is %s\n", p1->name);     // -> Nova
    printf("Second cat is %s\n", (p1+1)->name); // -> Shiro


     // Declare struct and a variable together
     struct bike {
        char *name;
        int mileage;
    } newbike;

    newbike.name = "Yamaha";
    newbike.mileage = 40;

    //  Declare struct and define an array of structures
    struct bike2 {
        char *name;
        int mileage;
    } newbikeArr[5];

    //  Declare, define, and initialize array of structures
    struct bike3 {
        char *name;
        int mileage;
    } newbikeInit[5] = {
        {"Honda", 45},
        {"Suzuki", 50},
        {"KTM", 35},
        {"BMW", 25},
        {"Royal Enfield", 30}
    };

    // Access one of them
    printf("Bike: %s, Mileage: %d\n", newbikeInit[2].name, newbikeInit[2].mileage);  // KTM

    return 0;
    
    return 0;
}