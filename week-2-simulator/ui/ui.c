#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    // same key as what core.c uses for the UI queue, so they connect to the same queue
    key_t ui_key = ftok("progfile_ui", 65);
    if (ui_key == -1) {
        perror("UI: ftok failed");
        return 1;
    }

    int ui_qid = msgget(ui_key, 0666 | IPC_CREAT);
    if (ui_qid == -1) {
        perror("UI: msgget failed");
        return 1;
    }

    struct msg_buffer message;
    message.msg_type = 1;   // type 1 = command, matches what core.c listens for
    char input[100];

    printf("UI: enter commands (PUSH x | POP | ENQUEUE x | DEQUEUE | STORE addr val | LOAD addr | ADD a b | EXIT)\n");

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = 0;   // strip the trailing newline from input

        strcpy(message.msg_text, input);
        // In System V IPC, msgsz is the size of the payload (excluding msg_type)
        if (msgsnd(ui_qid, &message, sizeof(message.msg_text), 0) == -1) {
            perror("UI: msgsnd failed");
        }

        if (strcmp(input, "EXIT") == 0) {
            printf("UI: sent exit command.\n");
            break;
        }
    }

    return 0;
}
