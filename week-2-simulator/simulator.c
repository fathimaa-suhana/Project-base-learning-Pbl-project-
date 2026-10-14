#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEM_SIZE 16
#define STACK_SIZE 10
#define QUEUE_SIZE 10

int memory[MEM_SIZE];
int stack[STACK_SIZE], stack_top = -1;
int queue[QUEUE_SIZE], q_front = 0, q_rear = -1, q_count = 0;

void push(int val) {
    if (stack_top < STACK_SIZE - 1) {
        stack[++stack_top] = val;
        printf("LOG: pushed %d to stack\n", val);
    } else {
        printf("LOG: ERROR stack overflow\n");
    }
}

void pop() {
    if (stack_top >= 0) {
        printf("LOG: popped %d from stack\n", stack[stack_top--]);
    } else {
        printf("LOG: ERROR stack underflow\n");
    }
}

void enqueue(int val) {
    if (q_count < QUEUE_SIZE) {
        q_rear = (q_rear + 1) % QUEUE_SIZE;
        queue[q_rear] = val;
        q_count++;
        printf("LOG: enqueued %d\n", val);
    } else {
        printf("LOG: ERROR queue full\n");
    }
}

void dequeue() {
    if (q_count > 0) {
        printf("LOG: dequeued %d\n", queue[q_front]);
        q_front = (q_front + 1) % QUEUE_SIZE;
        q_count--;
    } else {
        printf("LOG: ERROR queue empty\n");
    }
}

void store(int addr, int val) {
    if (addr >= 0 && addr < MEM_SIZE) {
        memory[addr] = val;
        printf("LOG: stored %d at mem[%d]\n", val, addr);
    } else {
        printf("LOG: ERROR invalid memory address\n");
    }
}

void load(int addr) {
    if (addr >= 0 && addr < MEM_SIZE) {
        printf("LOG: loaded %d from mem[%d]\n", memory[addr], addr);
    } else {
        printf("LOG: ERROR invalid memory address\n");
    }
}

void add(int a, int b) {
    printf("LOG: ADD result = %d\n", a + b);
}

int main() {
    char cmd[20];
    int a, b;

    printf("Mini CPU Simulator - commands: PUSH x | POP | ENQUEUE x | DEQUEUE | STORE addr val | LOAD addr | ADD a b | EXIT\n");

    while (1) {
        printf("> ");
        scanf("%s", cmd);

        if (strcmp(cmd, "PUSH") == 0) {
            scanf("%d", &a);
            push(a);
        } else if (strcmp(cmd, "POP") == 0) {
            pop();
        } else if (strcmp(cmd, "ENQUEUE") == 0) {
            scanf("%d", &a);
            enqueue(a);
        } else if (strcmp(cmd, "DEQUEUE") == 0) {
            dequeue();
        } else if (strcmp(cmd, "STORE") == 0) {
            scanf("%d %d", &a, &b);
            store(a, b);
        } else if (strcmp(cmd, "LOAD") == 0) {
            scanf("%d", &a);
            load(a);
        } else if (strcmp(cmd, "ADD") == 0) {
            scanf("%d %d", &a, &b);
            add(a, b);
        } else if (strcmp(cmd, "EXIT") == 0) {
            break;
        } else {
            printf("LOG: ERROR unknown command\n");
        }
    }

    return 0;
}