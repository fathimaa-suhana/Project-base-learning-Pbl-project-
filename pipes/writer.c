#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    mkfifo("myfifo", 0666);

    int fd = open("myfifo", O_WRONLY);
    char msg[] = "Hello from writer process!";
    write(fd, msg, strlen(msg) + 1);
    printf("Writer: message sent.\n");
    close(fd);
    return 0;
}