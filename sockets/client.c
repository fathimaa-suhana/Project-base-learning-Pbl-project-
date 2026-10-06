#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "mysock");

    connect(fd, (struct sockaddr *)&addr, sizeof(addr));

    char msg[] = "Hello from client!";
    write(fd, msg, strlen(msg) + 1);
    printf("Client: message sent.\n");

    char buf[100];
    read(fd, buf, sizeof(buf));
    printf("Client received: %s\n", buf);

    close(fd);
    return 0;
}
