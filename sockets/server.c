#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "mysock");

    unlink("mysock");
    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);
    printf("Server: waiting for client...\n");

    int client_fd = accept(server_fd, NULL, NULL);

    char buf[100];
    read(client_fd, buf, sizeof(buf));
    printf("Server received: %s\n", buf);

    char reply[] = "Hello from server!";
    write(client_fd, reply, strlen(reply) + 1);

    close(client_fd);
    close(server_fd);
    unlink("mysock");
    return 0;
}
