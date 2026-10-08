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
    int ui_qid = msgget(ui_key, 0666 | IPC_CREAT);

    struct msg_buffer message;
    message.msg_type = 1;   // type 1 = command, matches what core.c listens for
    char input[100];

    printf("UI: enter commands (PUSH x | POP | ADD a b | EXIT)\n");

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;   // strip the trailing newline from input

        strcpy(message.msg_text, input);
        msgsnd(ui_qid, &message, sizeof(message), 0);

        if (strcmp(input, "EXIT") == 0) {
            printf("UI: sent exit command.\n");
            break;
        }
    }

    return 0;
}
