#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
    long type;
    char text[100];
} Message;

int main() {
    key_t loggerKey = ftok("progfile_log", 66);
    if (loggerKey == -1) {
        perror("[LOGGER] ftok failed");
        return 1;
    }

    int loggerQueueId = msgget(loggerKey, 0666 | IPC_CREAT);
    if (loggerQueueId == -1) {
        perror("[LOGGER] msgget failed");
        return 1;
    }

    Message event;
    FILE *logFile = fopen("log.txt", "a");

    if (logFile == NULL) {
        printf("[LOGGER] ERROR: could not open log file\n");
        return 1;
    }

    printf("[LOGGER] Ready, listening for events from Core...\n");

    while (1) {
        // In System V IPC, msgsz is the size of the payload (excluding type)
        if (msgrcv(loggerQueueId, &event, sizeof(event.text), 2, 0) == -1) {
            perror("[LOGGER] msgrcv failed");
            break;
        }
        printf("[LOGGER] logged: %s\n", event.text);

        fprintf(logFile, "%s\n", event.text);
        fflush(logFile);

        if (strcmp(event.text, "Core process exiting now") == 0) {
            printf("[LOGGER] shutdown signal received, closing.\n");
            break;
        }
    }

    fclose(logFile);
    if (msgctl(loggerQueueId, IPC_RMID, NULL) == -1) {
        perror("[LOGGER] msgctl IPC_RMID failed");
    }
    return 0;
}
