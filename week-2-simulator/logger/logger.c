#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    // same key as what core.c uses for the log queue, so they connect to the same queue
    key_t log_key = ftok("progfile_log", 66);
    int log_qid = msgget(log_key, 0666 | IPC_CREAT);

    struct msg_buffer incoming;
    FILE *fp = fopen("log.txt", "a");   // "a" = append, so logs build up over runs instead of overwriting

    printf("Logger: waiting for events...\n");

    while (1) {
        // msg_type 2 = result/event messages, matches what core.c sends
        msgrcv(log_qid, &incoming, sizeof(incoming), 2, 0);
        printf("Logger received: %s\n", incoming.msg_text);
        fprintf(fp, "%s\n", incoming.msg_text);
        fflush(fp);   // force write to disk immediately instead of buffering

        if (strcmp(incoming.msg_text, "Core shutting down") == 0) {
            break;
        }
    }

    fclose(fp);
    msgctl(log_qid, IPC_RMID, NULL);   // clean up the queue once done
    return 0;
}