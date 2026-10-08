#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Receiver got: %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
