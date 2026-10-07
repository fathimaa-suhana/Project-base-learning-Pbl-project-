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
    int loggerQueueId = msgget(loggerKey, 0666 | IPC_CREAT);

    Message event;
    FILE *logFile = fopen("log.txt", "a");

    if (logFile == NULL) {
        printf("[LOGGER] ERROR: could not open log file\n");
        return 1;
    }

    printf("[LOGGER] Ready, listening for events from Core...\n");

    while (1) {
        msgrcv(loggerQueueId, &event, sizeof(event), 2, 0);
        printf("[LOGGER] logged: %s\n", event.text);

        fprintf(logFile, "%s\n", event.text);
        fflush(logFile);

        if (strcmp(event.text, "Core process exiting now") == 0) {
            printf("[LOGGER] shutdown signal received, closing.\n");
            break;
        }
    }

    fclose(logFile);
    msgctl(loggerQueueId, IPC_RMID, NULL);
    return 0;
}
