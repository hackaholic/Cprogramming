/*
        Author: Kumar Shubham

*/


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MAX_PATHNAME_SIZE 100
#define MAX_MESSAGE_SIZE 100


static struct mymsg {
        int msg_type;
        char text[MAX_MESSAGE_SIZE];
    } msg;

int open_msg_queue(key_t key) {
    int id;
    if ((id = msgget(key, IPC_CREAT | 0660)) == -1) {
        printf("Error while creating msg Queue\n");
        return -1;
    }
    return id;
}

int msg_snd(int id, struct mymsg *buf) {
    int status;
    size_t msg_size;
    msg_size = sizeof(struct mymsg);
    if((status = msgsnd(id, buf, msg_size, 0)) == -1) {
        printf("Error in appending msg to queue %i\n, %d\n", id, EXIT_FAILURE);
        return status;
    }
    return status;
}

size_t msg_rcv(int id, struct mymsg *buf) {
    size_t msg_size;
    int length;
    length = sizeof(struct mymsg);
    if ((msg_size = msgrcv(id, buf, length, 0, 0)) == -1) {
        printf("Error in fetching the msg from the queue: %i\n", id);
    }
    return msg_size;
}

int main(int argc, char *argv[]) {
    key_t msg_queue_key;
    int msg_queue_id;
    int status;
    char filepath[MAX_PATHNAME_SIZE];
    size_t msg_size;
    char mode[2];

    if(argc < 3) {
        printf("Usage: binary <path> <s/r>");
        exit(1);
    }
    // exit if filename is larger than MAX_PATHNAME_SIZE
    if(strlen(argv[1]) > MAX_PATHNAME_SIZE) {
        printf("File path too long\n");
        exit(1);
    }
    strcpy(filepath, *++argv);
    printf("filepath: %s\n", filepath);
    
    // Create IPC identier key
    if ((msg_queue_key = ftok(filepath, 'a')) == -1) {
        printf("Error in creating key for message queue\n");
        exit(1);
    }
    
    printf("key: %x\n", msg_queue_key);
    msg_queue_id = open_msg_queue(msg_queue_key);
    if (msg_queue_id == -1) {
        exit(1);
    }
    printf("msg_queue_id: %i\n", msg_queue_id);
    strcpy(mode, *++argv);
    if (strcmp(mode, "s") == 0) {
        msg.msg_type = 1;
        strcpy(msg.text, "Hello World");
        status = msg_snd(msg_queue_id, &msg);
    }
    if (strcmp(mode, "r") == 0) {
        msg_size = msg_rcv(msg_queue_id, &msg);
        printf("msg: %s\n", msg.text);
    }

}