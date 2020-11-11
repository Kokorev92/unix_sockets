#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/un.h>
#include <signal.h>

int sock;
int client_send_quit_message;
struct sockaddr_un name = {AF_UNIX, "test.sock" }; 

struct arguments_t {
    int count;
    char* argv[];
};

void close_socket(){
    unlink(name.sun_path);
    close(sock); 
}

int client_proc(int client_sock) {
    int len;
    char* text;

    while(true) {
    if(read(client_sock, &len, sizeof(len)) == 0)
        return 0;
    text = (char*)malloc(len);
    read(client_sock, text, len);
    printf("%s\n", text);

    if(!strcmp(text, "quit")) 
        return 1;
    }
    free(text);
}

void exit_handler(int s) {
    printf("Server exit...\n");
    close_socket();
    exit(1);
}

int main(int argc, char* argv[]) {
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    bind(sock, (struct sockaddr*)&name, SUN_LEN(&name));
    listen(sock, 2);

    struct sigaction sig_ctrl_c;
    sig_ctrl_c.sa_handler = exit_handler;
    sigemptyset(&sig_ctrl_c.sa_mask);
    sig_ctrl_c.sa_flags = 0;

    sigaction(SIGINT, &sig_ctrl_c, NULL);

    do {
        int client_sock;
        client_sock = accept(sock, NULL, NULL);
        client_send_quit_message = client_proc(client_sock);
        close(client_sock);
    } while (!client_send_quit_message);
    close_socket();
   return 0;
}
