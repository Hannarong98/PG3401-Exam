#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int server_socket;
    int port;

    char client_message_buffer[256];
    char received_buffer[256];

    if((server_socket  = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket");
        return 1;
    } else {
        printf("Opening a socket...\n");
    }

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-server") == 0){
            port = atoi(argv[i+1]);
        }
    }

    struct sockaddr_in socket_address = {0};
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(server_socket,(struct sockaddr *) &socket_address, sizeof(socket_address)) < 0){
        printf("Connect");
        return 1;
    } else {
        printf("Established a connection\n");
    }

    memset(received_buffer, 0, sizeof(received_buffer));
    memset(client_message_buffer, 0, sizeof(client_message_buffer));

    int bytes_read = recv(server_socket, received_buffer, sizeof(received_buffer), MSG_WAITFORONE);

    if(bytes_read < 0){
        perror("Receive");
        close(server_socket);
        return 1;
    } else {
        while(1){
            int selected_choice;

            printf("Attempting to connect to server %s, do you wish to continue y/n?\n", received_buffer);
            selected_choice = getchar();
            getchar();

            if(selected_choice == 'Y' || selected_choice == 'y'){
                char *msg = "y";
                sprintf(client_message_buffer, "%s", msg);
                printf("%s\n", client_message_buffer);
            } else if(selected_choice == 'N' || selected_choice == 'n'){
                char *msg = "n";
                sprintf(client_message_buffer, "%s", msg);
                printf("%s\n", client_message_buffer);
            } else {
                char *msg = "n";
                printf("%s\n", client_message_buffer);
                sprintf(client_message_buffer, "%s", msg);
            }
            break;
        }

        send(server_socket, client_message_buffer, strlen(client_message_buffer) + 1, 0);

        bytes_read = recv(server_socket, received_buffer, sizeof(received_buffer), MSG_WAITFORONE);

        if(strcmp(received_buffer, "CONNECT") == 0){
            while(1){
                memset(client_message_buffer, 0, sizeof(client_message_buffer));
                memset(received_buffer, 0, sizeof(received_buffer));
                printf("Send something to server\n");
                fgets(client_message_buffer, sizeof(client_message_buffer), stdin);
                client_message_buffer[strlen(client_message_buffer) - 1] = '\0';
                while(strlen(client_message_buffer) == 0){
                    printf("You can not send empty messages\n");
                    fgets(client_message_buffer, sizeof(client_message_buffer), stdin);
                    client_message_buffer[strlen(client_message_buffer) - 1] = '\0';
                }
                if(strcmp(client_message_buffer, "quit") == 0){
                    send(server_socket, client_message_buffer, strlen(client_message_buffer), 0);
                    close(server_socket);
                    return 0;
                }
                int bytes_sent = send(server_socket, client_message_buffer, strlen(client_message_buffer), 0);

                if(bytes_sent < 0){
                    memset(received_buffer, 0, sizeof(received_buffer));
                    close(server_socket);
                    break;
                } else {
                    printf("[Client] >>>> %s\n", client_message_buffer);
                    recv(server_socket, received_buffer, sizeof(received_buffer), MSG_WAITFORONE);
                    printf("%s <<<< [Server]\n", received_buffer);
                }
            }
            close(server_socket);
            return 0;
        }
    }
    close(server_socket);
    return 0;
}

