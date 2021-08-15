#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define MAX_PATHNAME_SIZE 100
#define MAX_SHARED_BYTES 100

key_t get_key(char *filename, int seed) {
    key_t key;
    if ((key = ftok(filename, seed)) == -1) {
        printf("Error: %i, In creating key\n", errno);
    }
    return key;
}

int create_shared_memory(key_t key) {
    int shmid;
    if((shmid = shmget(key, MAX_SHARED_BYTES, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
        printf("Error: %i, in creating share memory id for key: %x\n", errno, key);
        if(EEXIST) {
            printf("Shared memory already exist for key %x\n", key);
        }
        exit(EXIT_FAILURE);
    }
    return shmid;
}

int open_shared_memory(key_t key) {
    int shmid;
    if((shmid = shmget(key, MAX_SHARED_BYTES, 0666)) == -1) {
        printf("Error: %i, in opening share memory id for key: %x\n", errno, key);
        exit(EXIT_FAILURE);
    }
    return shmid;
}

int detach_memory(const void *shmaddr) {
    return shmdt(shmaddr);
}

void shared_memory_stats(int shmid) {
    int status;
    struct shmid_ds shm_meta;
    if((status = shmctl(shmid, IPC_STAT, &shm_meta)) == -1) {
        printf("Error: %i, in getting shared memory %i status\n", errno, shmid);
    }
    printf("Shared memory %i status...\n", shmid);
    printf("Segment size: %lu\n", shm_meta.shm_segsz);
    printf("Last attached time: %s\n", asctime(gmtime(&shm_meta.shm_atime)));
    printf("Last detach time: %s\n", asctime(gmtime(&shm_meta.shm_dtime)));
    printf("Last changed time: %s\n", asctime(gmtime(&shm_meta.shm_ctime)));
    printf("Current attaches: %lu\n", shm_meta.shm_nattch);
}

int delete_shared_memory(int shmid) {
    int status;
    if((status = shmctl(shmid, IPC_RMID, 0)) == -1) {
        printf("ERROR: %i in shared memory %i\n", errno, shmid);
        exit(EXIT_FAILURE);
    }
    return status;
}
void usage() {
    printf("binary <key_file> <c/r/w/d/s> <text>");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int choice;
    int shmid;
    key_t key;
    char filename[MAX_PATHNAME_SIZE];
    char *text;
    char seed = 'a';

    if (argc <= 2) {
        usage();
    }

    strcpy(filename, argv[1]);
    choice = argv[2][0];
    if(( key = get_key(filename, seed)) == -1){
        exit(EXIT_FAILURE);
    }
    switch (choice) {
        case 'c':
            shmid = create_shared_memory(key);
            printf("Shared memoery is created key: %x, shmid:%i", key, shmid);
        case 'w':
            if (argc < 3) {
                usage();
                exit(1);
            }
            shmid = open_shared_memory(key);
            if((text = shmat(shmid, 0, 0)) == NULL) {
               printf("Error: %i, in attaching to memory for shmid: %i", errno, shmid);
               exit(EXIT_FAILURE);
            }
            strcpy(text, argv[3]);
            detach_memory(text);
            break;
        case 'r':
            shmid = open_shared_memory(key);
            if((text = shmat(shmid, 0, 0)) == NULL) {
               printf("Error: %i, in attaching to memory for shmid: %i", errno, shmid);
               exit(EXIT_FAILURE);
            }
            printf("text: %s\n", text);
            detach_memory(text);
            break;
        case 's':
            shmid = open_shared_memory(key);
            shared_memory_stats(shmid);
            break;
        case 'd': 
            shmid = open_shared_memory(key);
            delete_shared_memory(shmid);
            break;
        default: 
            usage();    
    }
}