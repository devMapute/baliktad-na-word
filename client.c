#include "headers.h"

int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];
    
    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    
    printf("Socket created successfully\n");
    
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    char ip_address[100];
    printf("Enter server IP address: ");
    fgets(ip_address, sizeof(ip_address), stdin);
    ip_address[strcspn(ip_address, "\n")] = 0; // Remove trailing newline
    server_addr.sin_addr.s_addr = inet_addr(ip_address); // Get user input for IP address
    
    // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Send a connection request to the server, which is waiting at accept():
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");

    while(1){
        // Get input from the user:
        printf("Enter message: ");
        fgets(client_message,2000,stdin);
        
        // Send the message to server:
        if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
            printf("Unable to send message\n");
            return -1;
        }

        client_message[strcspn(client_message,"\n")] = 0;
        if (!strcmp(client_message, "exit")){
            close(socket_desc);
            printf("\n");
            return 0;
        }

        // Receive the server's response:
        if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
            printf("Error while receiving server's msg\n");
            return -1;
        }
        
        printf("Server's response: %s\n",server_message);
        
        // Clean buffers:
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
    }
    

}