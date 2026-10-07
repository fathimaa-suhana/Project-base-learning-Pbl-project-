#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

#define STACK_SIZE 10
int stack[STACK_SIZE], stack_top = -1;

void push(int val, char *out) {
    if (stack_top < STACK_SIZE - 1) {
        stack[++stack_top] = val;
        sprintf(out, "pushed %d to stack", val);
    } else {
        sprintf(out, "ERROR stack overflow");
    }
}

void pop(char *out) {
    if (stack_top >= 0) {
        sprintf(out, "popped %d from stack", stack[stack_top--]);
    } else {
        sprintf(out, "ERROR stack underflow");
    }
}

void add(int a, int b, char *out) {
    sprintf(out, "ADD result = %d", a + b);
}

int main() {
    // key_t generates a unique IPC key from a filename, used to identify the message queue
    key_t ui_key = ftok("progfile_ui", 65);
    key_t log_key = ftok("progfile_log", 66);

    int ui_qid = msgget(ui_key, 0666 | IPC_CREAT);   // queue for receiving from UI
    int log_qid = msgget(log_key, 0666 | IPC_CREAT); // queue for sending to Logger

    struct msg_buffer incoming, outgoing;

    printf("Core: waiting for commands...\n");

    while (1) {
        // msg_type 1 = command messages coming from UI
        msgrcv(ui_qid, &incoming, sizeof(incoming), 1, 0);
        printf("Core received: %s\n", incoming.msg_text);

        if (strcmp(incoming.msg_text, "EXIT") == 0) {
            outgoing.msg_type = 2;
            sprintf(outgoing.msg_text, "Core shutting down");
            msgsnd(log_qid, &outgoing, sizeof(outgoing), 0);
            break;
        }

        char cmd[20];
        int a, b;
        char result[100];

        sscanf(incoming.msg_text, "%s %d %d", cmd, &a, &b);

        if (strcmp(cmd, "PUSH") == 0) {
            push(a, result);
        } else if (strcmp(cmd, "POP") == 0) {
            pop(result);
        } else if (strcmp(cmd, "ADD") == 0) {
            add(a, b, result);
        } else {
            sprintf(result, "ERROR unknown command");
        }

        // msg_type 2 = result/event messages going to Logger
        outgoing.msg_type = 2;
        strcpy(outgoing.msg_text, result);
        msgsnd(log_qid, &outgoing, sizeof(outgoing), 0);
    }

    return 0;
}