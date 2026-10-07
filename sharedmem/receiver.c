#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#define KEY 42
#define SHM_SIZE 1024

int main() {
    key_t key = ftok("proj.shm", 65);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    printf("Receiver: data read from shared memory: %s\n", data);

    shmdt(data);
    return 0;
}