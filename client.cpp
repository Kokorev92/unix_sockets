#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

struct sockaddr_un name = {AF_UNIX, "test.sock"};
char buffer[256];

void write_message(int sock, char* data) {
    int len = strlen(data) + 1;
    write(sock, &len, sizeof(len));
    write(sock, data, len);
}

int main(int argc, char* argv[]) {
    int sock;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    int connected = connect(sock, (struct sockaddr*)&name, SUN_LEN(&name));
    if (connected < 0) {
        std::cout << "Connection error!\n";
    }
    for(int i = 1; i < argc; i++) {
        strcpy(buffer, argv[i]);
        write_message(sock, buffer);
    }
    close(sock);

    return 0;
}
