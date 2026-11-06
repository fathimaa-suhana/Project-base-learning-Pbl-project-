#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MEM_SIZE 16
#define STACK_SIZE 10
#define QUEUE_SIZE 10

/* Message buffer matching UI and Logger structure */
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

/* Simulated hardware components */
int memory[MEM_SIZE];
int stack[STACK_SIZE], stack_top = -1;
int queue[QUEUE_SIZE], q_front = 0, q_rear = -1, q_count = 0;

/* Helper function to forward execution log messages to the Logger process */
void send_to_logger(int logger_qid, const char *text) {
    struct msg_buffer msg;
    msg.msg_type = 2; /* Logger listens specifically for msg_type = 2 */
    
    strncpy(msg.msg_text, text, sizeof(msg.msg_text) - 1);
    msg.msg_text[sizeof(msg.msg_text) - 1] = '\0';

    /* In System V IPC, msgsz is only the size of the payload text */
    if (msgsnd(logger_qid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("[CORE] msgsnd to logger failed");
    } else {
        printf("[CORE] Sent to logger: %s\n", text);
    }
}

int main() {
    /* Ensure token files exist so ftok() produces valid keys */
    FILE *f_ui = fopen("progfile_ui", "a");
    if (f_ui) fclose(f_ui);
    FILE *f_log = fopen("progfile_log", "a");
    if (f_log) fclose(f_log);

    /* 1. Connect to UI message queue (key 65) */
    key_t ui_key = ftok("progfile_ui", 65);
    if (ui_key == -1) {
        perror("[CORE] ftok for UI queue failed");
        return 1;
    }
    int ui_qid = msgget(ui_key, 0666 | IPC_CREAT);
    if (ui_qid == -1) {
        perror("[CORE] msgget for UI queue failed");
        return 1;
    }

    /* 2. Connect to Logger message queue (key 66) */
    key_t logger_key = ftok("progfile_log", 66);
    if (logger_key == -1) {
        perror("[CORE] ftok for Logger queue failed");
        return 1;
    }
    int logger_qid = msgget(logger_key, 0666 | IPC_CREAT);
    if (logger_qid == -1) {
        perror("[CORE] msgget for Logger queue failed");
        return 1;
    }

    printf("[CORE] Process started successfully. Waiting for UI commands...\n");

    struct msg_buffer ui_msg;
    char log_buf[100];
    char cmd[20];
    int a, b;

    while (1) {
        /* Receive next command from UI (msg_type = 1) */
        if (msgrcv(ui_qid, &ui_msg, sizeof(ui_msg.msg_text), 1, 0) == -1) {
            perror("[CORE] msgrcv from UI failed");
            break;
        }

        printf("[CORE] Received command: \"%s\"\n", ui_msg.msg_text);

        /* Parse command name with width limit to prevent buffer overflow */
        cmd[0] = '\0';
        if (sscanf(ui_msg.msg_text, "%19s", cmd) != 1) {
            continue;
        }

        /* Execute requested operation */
        if (strcmp(cmd, "PUSH") == 0) {
            if (sscanf(ui_msg.msg_text, "%*s %d", &a) == 1) {
                if (stack_top < STACK_SIZE - 1) {
                    stack[++stack_top] = a;
                    snprintf(log_buf, sizeof(log_buf), "pushed %d to stack", a);
                } else {
                    snprintf(log_buf, sizeof(log_buf), "ERROR: stack overflow");
                }
            } else {
                snprintf(log_buf, sizeof(log_buf), "ERROR: missing value for PUSH");
            }
            send_to_logger(logger_qid, log_buf);

        } else if (strcmp(cmd, "POP") == 0) {
            if (stack_top >= 0) {
                int val = stack[stack_top--];
                snprintf(log_buf, sizeof(log_buf), "popped %d from stack", val);
            } else {
                snprintf(log_buf, sizeof(log_buf), "ERROR: stack underflow");
            }
            send_to_logger(logger_qid, log_buf);

        } else if (strcmp(cmd, "ENQUEUE") == 0) {
            if (sscanf(ui_msg.msg_text, "%*s %d", &a) == 1) {
                if (q_count < QUEUE_SIZE) {
                    q_rear = (q_rear + 1) % QUEUE_SIZE;
                    queue[q_rear] = a;
                    q_count++;
                    snprintf(log_buf, sizeof(log_buf), "enqueued %d", a);
                } else {
                    snprintf(log_buf, sizeof(log_buf), "ERROR: queue full");
                }
            } else {
                snprintf(log_buf, sizeof(log_buf), "ERROR: missing value for ENQUEUE");
            }
            send_to_logger(logger_qid, log_buf);

        } else if (strcmp(cmd, "DEQUEUE") == 0) {
            if (q_count > 0) {
                int val = queue[q_front];
                q_front = (q_front + 1) % QUEUE_SIZE;
                q_count--;
                snprintf(log_buf, sizeof(log_buf), "dequeued %d", val);
            } else {
                snprintf(log_buf, sizeof(log_buf), "ERROR: queue empty");
            }
            send_to_logger(logger_qid, log_buf);

        } else if (strcmp(cmd, "STORE") == 0) {
            if (sscanf(ui_msg.msg_text, "%*s %d %d", &a, &b) == 2) {
                if (a >= 0 && a < MEM_SIZE) {
                    memory[a] = b;
                    snprintf(log_buf, sizeof(log_buf), "stored %d at mem[%d]", b, a);
                } else {
                    snprintf(log_buf, sizeof(log_buf), "ERROR: invalid memory address");
                }
            } else {
                snprintf(log_buf, sizeof(log_buf), "ERROR: STORE requires addr and val");
            }
            send_to_logger(logger_qid, log_buf);

        } else if (strcmp(cmd, "LOAD") == 0) {
            if (sscanf(ui_msg.msg_text, "%*s %d", &a) == 1) {
                if (a >= 0 && a < MEM_SIZE) {
                    snprintf(log_buf, sizeof(log_buf), "loaded %d from mem[%d]", memory[a], a);
                } else {
                    snprintf(log_buf, sizeof(log_buf), "ERROR: invalid memory address");
                }
            } else {
                snprintf(log_buf, sizeof(log_buf), "ERROR: missing address for LOAD");
            }
            send_to_logger(logger_qid, log_buf);

        } else if (strcmp(cmd, "ADD") == 0) {
            if (sscanf(ui_msg.msg_text, "%*s %d %d", &a, &b) == 2) {
                snprintf(log_buf, sizeof(log_buf), "ADD result = %d", a + b);
            } else {
                snprintf(log_buf, sizeof(log_buf), "ERROR: ADD requires two values");
            }
            send_to_logger(logger_qid, log_buf);

        } else if (strcmp(cmd, "EXIT") == 0) {
            /* Send exact shutdown signal expected by logger.c */
            send_to_logger(logger_qid, "Core process exiting now");
            printf("[CORE] EXIT command received. Shutting down.\n");
            break;

        } else {
            snprintf(log_buf, sizeof(log_buf), "ERROR: unknown command");
            send_to_logger(logger_qid, log_buf);
        }
    }

    /* Clean up the UI message queue before exiting */
    if (msgctl(ui_qid, IPC_RMID, NULL) == -1) {
        perror("[CORE] msgctl IPC_RMID for UI queue failed");
    } else {
        printf("[CORE] UI message queue removed successfully.\n");
    }

    return 0;
}
