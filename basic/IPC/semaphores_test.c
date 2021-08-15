#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include<sys/types.h>
#include <sys/sem.h>
#include <errno.h>

#define MAX_PATHNAME_SIZE 100
#define MAX_MEMBER 10
#define COUNTER 1

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
    struct seminfo *__buf;
    void *__pad;
};

key_t get_key(char *path, char seed) {
    key_t key;
    if((key = ftok(path, seed)) == -1) {
        printf("Error in creating key");
    }
    return key;
}

int create_semaphores(key_t key, int members) {
    int sid;
    union semun semopts;
    if(!members || members > MAX_MEMBER) {
        return -1;
    }
    if((sid = semget(key, members, IPC_CREAT| IPC_EXCL | 0660)) == -1) {
        printf("Error in creating shemaphore\n");
        if(EEXIST) {
        printf("ERROR: %i, Semaphore already Exists for key: %x\n", errno, key);
        }
         return sid;
    }
    semopts.val = COUNTER;
    for(int i=0;i<members;i++) {
        semctl(sid, i, SETVAL, semopts);
    }
    return sid;
}

int open_semaphore(key_t key) {
    int sid;
    if ((sid = semget(key, 0, 0660)) == -1) {
        printf("Error: %i,in opening semaphores for key\n", errno);
    }
    return sid;
}

int get_val(int sid, int member) {
    int val;
    if(( val = semctl(sid, member, GETVAL, 0)) ==  -1) {
        printf("ERROR: %i, Error in getting val of member %i of semaphore %i", errno, member, sid);
        return val;
    }
    return val;
}

int get_member_count(int sid) {
    union semun semopts;
    struct semid_ds semid_structure;
    semopts.buf = &semid_structure;
    semctl(sid, 0, IPC_STAT, semopts);
    return semopts.buf->sem_nsems;
}

int get_members_val(int sid) {
    union semun semopts;
    int status;
    int member = get_member_count(sid);
    ushort arr_val[member-1];
    semopts.array = arr_val;
    if((status = semctl(sid, 0, GETALL, semopts)) == -1) {
        printf("Error: %i, Error in geting val for semaphores %i\n", errno, sid);
        return status;
    }
    for(int i=0;i<member;i++){
        printf("Member: %i, val: %i\n", i, arr_val[i]);
    }
    return status;
}

int lock_sem(int sid, int member) {
    struct sembuf lock = {member, -1, IPC_NOWAIT};
    int status;
    if (member < 0 || get_member_count(sid)-1 < member) {
        printf("Member %i out of range\n", member);
        return -1;
    }
    if ((status = semop(sid, &lock, 1)) == -1) {
        printf("Error, %i, failed to get lock on member %i\n", errno, member);        
    }
    return status;
}

int unlock_sem(int sid, int member) {
    struct sembuf unlock = {member, 1, IPC_NOWAIT};
    int status, val;
    if (member < 0 || get_member_count(sid)-1 < member) {
        printf("Member %i out of range\n", member);
        return -1;
    }
    val = get_val(sid, member);
    if( val == COUNTER) {
        printf("Member: %i is already Unlocked\n", member);
        return 1;
    }
    if ((status = semop(sid, &unlock, 1)) == -1) {
        printf("Error, %i, failed to unlock member %i\n", errno, member);        
    }
    return status;
}

int remove_sem(int sid) {
    int status;
    if((status = semctl(sid, 0, IPC_RMID, 0)) == -1) {
        printf("Error: %i, in removing %i semaphore set\n", errno, sid);
    }
    else {
        printf("Semaphore %i removed\n", sid);
    }
    return status;
}

void usage() {
    printf("Usage: binary <c nsems> <l/u member> <d>\n");
}

int main(int argc, char *argv[]) {
    key_t key;
    int sid, n;
    char filename[MAX_PATHNAME_SIZE], seed;
    char choice;

    seed = 'a';
    if(argc == 2) {
        usage();
        exit(1);
    }
    
    strcpy(filename, argv[1]);
    choice = argv[2][0];
    key = get_key(filename, seed);
    
    if(!key) {
        exit(1);
    }
    
    switch(choice) {
        case 'c':
            if(argc != 4)
                usage();
            sid = create_semaphores(key, atoi(argv[3]));
            break;
        case 'l':
            if(argc != 4)
                usage(); 
            sid = open_semaphore(key);
            lock_sem(sid, atoi(argv[3]));
            break;
        case 'u':
            if(argc != 4)
                usage(); 
            sid = open_semaphore(key);
            unlock_sem(sid, atoi(argv[3]));
            break;
        case 'g':
            sid = open_semaphore(key);
            get_members_val(sid);
            break;
        case 'd':
            sid = open_semaphore(key);
            remove_sem(sid);
            break;
        default:
            usage();
    }
}