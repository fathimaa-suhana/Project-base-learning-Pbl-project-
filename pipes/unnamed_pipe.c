#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid > 0) {
        close(fd[0]);
        char msg[] = "Hello from parent!";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    } else {
        close(fd[1]);
        char buf[100];
        read(fd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        close(fd[0]);
    }
    return 0;
}