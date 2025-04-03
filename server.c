#include "headers.h"

int isVowel(char c){
    int lowercase_vowel, uppercase_vowel;
    // evaluates to 1 if variable c is a lowercase vowel
    lowercase_vowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');

    // evaluates to 1 if variable c is a uppercase vowel
    uppercase_vowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');

    // evaluates to 1 (true) if c is a vowel
    if (lowercase_vowel || uppercase_vowel){
        return 1;
    }
    else{
        return 0;
    }


}

int main(void)
{
    int socket_desc, client_sock, client_size;
    int string_len;
    int consonant_flag;
    int i,j, ptr;
    char c;
    struct sockaddr_in server_addr, client_addr;
    char server_message[2000], client_message[2000];
    
    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    
    /* Create a socket that returns a socket descriptor; this will be used
       to refer to the socket later on in the code. The server-side code
       keeps the address information of both the server and the client in
       a variable of type sockaddr_in, which is a struct.
    */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    
    // Initialize the server address by the port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Bind the socket descriptor to the server address (the port and IP):
    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");
    
    // Turn on the socket to listen for incoming connections:
    if(listen(socket_desc, 1) < 0){
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections.....\n");
    
    /* Store the client’s address and socket descriptor by accepting an
       incoming connection. The server-side code stops and waits at accept()
       until a client calls connect().
    */
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, (socklen_t *)&client_size);
    
    if (client_sock < 0){
        printf("Can't accept\n");
        return -1;
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    // Receive client's message:
    while(1){
        if (recv(client_sock, client_message, sizeof(client_message), 0) < 0){
            printf("Couldn't receive\n");
            return -1;
        }
        client_message[strcspn(client_message,"\n")] = 0;
        if (!strcmp(client_message, "exit")){
            close(client_sock);
            close(socket_desc);
            printf("\n");
            return 0;
        }
        printf("Msg from client: %s\n", client_message);

        string_len = strlen(client_message);
        printf("String length: %d\n", string_len);
        ptr = string_len-1;
        // Last letter is consonant
        consonant_flag = !isVowel(client_message[ptr]);
        for (i = string_len-1; i > 0; i--){
            if (consonant_flag){
                for ( j = i-2; j <= ptr; j++){
                    printf("%c", client_message[j]);
                }
                consonant_flag = 0;
                printf("\n");
                ptr = i-2;
                i=i-2;

                for (i = 0; i < ptr; i ++){
                    printf("%c",client_message[i]);
                }
                printf("\n");
                break;
            } else{
                for ( j = i-1; j <= ptr; j++){
                    printf("%c", client_message[j]);
                }
                printf("\n");
                ptr = i-1;
                i--;
                
                for (i = 0; i < ptr; i ++){
                    printf("%c",client_message[i]);
                }
                printf("\n");
                break;
            }
            // else if (isVowel(client_message[i])){
            //     for ( j = i-1; j < ptr; j++){
            //         printf("%c", client_message[j]);
            //     }
            //     printf("\n");
            //     ptr = i-1;
            //     i--;
            // }
            
        }

        


        strcpy(server_message, "This is the server's message.");
        if (send(client_sock, server_message, strlen(server_message), 0) < 0){
            printf("Can't send\n");
            return -1;
        }

        // Clean buffers
        memset(server_message, '\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));       

    }
    // if (recv(client_sock, client_message, sizeof(client_message), 0) < 0){
    //     printf("Couldn't receive\n");
    //     return -1;
    // }
    // printf("Msg from client: %s\n", client_message);
    
    // // Respond to client:
    // strcpy(server_message, "This is the server's message.");
    
    // if (send(client_sock, server_message, strlen(server_message), 0) < 0){
    //     printf("Can't send\n");
    //     return -1;
    // }
    
    // // Closing the socket:
    // close(client_sock);
    // close(socket_desc);
    
    // return 0;
}
