#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int port;
    char *server_id;
    int server_socket;
    char server_message_buffer[256];
    char received_buffer[256];

    struct sockaddr_in socket_address = {0};

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-port") == 0){
            port = atoi(argv[i+1]);
            printf("port:%s\n", argv[i+1]);
        }

        if(strcmp(argv[i], "-id") == 0){
            server_id = malloc(sizeof(char) * (strlen(argv[i+1]) + 1));
            strcpy(server_id, argv[i+1]);
        }
    }

    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket");
        return 1;
    } else {
        printf("Socket is now opened...\n");
    }

    if(bind(server_socket, (struct sockaddr *) &socket_address, sizeof(socket_address)) < 0){
        perror("Bind");
        return 1;
    } else {
        printf("This address is now port binded to :%i.\n", port);
    }

    int listen_status = listen(server_socket, 5);

    if(listen_status < 0){
        perror("Listen");
        return 1;
    } else {
        printf("Listening for incoming connection...\n");
    }

    struct sockaddr_in client_socket_address = {0};


    while(1){

        printf("Waiting for a client...\n");
        int client_socket = accept(server_socket, (struct sockaddr *) &client_socket_address, (socklen_t *) &client_socket_address);

        if(client_socket < 0){
            perror("Accept");
            close(client_socket);
            return 1;
        }

        printf("Accepted new client.\n");

        sprintf(server_message_buffer, "%s", server_id);

        int bytes_sent = send(client_socket, server_message_buffer, strlen(server_message_buffer) + 1, 0);
        if(bytes_sent < 0){
            perror("Send");
            close(client_socket);
            close(server_socket);
            return 1;
        }

        int bytes_read = recv(client_socket, received_buffer, sizeof(received_buffer), MSG_WAITFORONE);

        if(bytes_read < 0){
            perror("Receive");
            close(client_socket);
            close(server_socket);
            return 1;
        }

        if(strcmp(received_buffer, "y") == 0){

            printf("Client wants to communicate.\n");
            memset(server_message_buffer, 0, sizeof(server_message_buffer));
            int bytes_sent = send(client_socket, "CONNECT", 8, 0);

            if(bytes_sent < 0){
                perror("Send");
                close(client_socket);
                close(server_socket);
                return 1;
            }

            memset(received_buffer, 0, sizeof(received_buffer));
            while(1){
                recv(client_socket, received_buffer, sizeof(server_message_buffer), MSG_WAITFORONE);
                if(strlen(received_buffer) == 0){
                    close(client_socket);
                    break;
                }
                printf("%s <<<< [Client]\n", received_buffer);
                memset(server_message_buffer, 0, sizeof(server_message_buffer));
                strcpy(server_message_buffer, received_buffer);
                send(client_socket, server_message_buffer, strlen(received_buffer), 0);
                printf("[Server] >>>> %s\n", server_message_buffer);
                memset(received_buffer, 0, sizeof(received_buffer));
            }
        } else {
            printf("Client wish to disconnect \n");
            send(client_socket, "DISCONNECT", 11, 0);
            recv(client_socket, "", 1, MSG_DONTWAIT);
            close(client_socket);
        }
    }

    close(server_socket);
    free(server_id);
    return 0;
}

