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

int isOneSyllable(char *word, char *output){
    char words[10][10] = {"ng", "ang", "hays", "mga"};

    for (int i = 0; i < 4; i++){
        if (strcmp(word, words[i]) == 0){
            return 1;
        }
    }
    return 0;

}

void transformWord(char *word, char *output) {
    int len = strlen(word);
    int ptr = len - 1;
    if (len <= 1) {
        strcpy(output, word); // For single letters, just copy as is
        return;
    } else if (len <= 4) {
        int is_one_syllable = isOneSyllable(word, output);
        if (is_one_syllable) {
            printf("One-syllable word detected: %s\n", word);
            strcpy(output, word); // For one-syllable words, just copy as is
            printf("Transformed: %s\n", output);
            return;
        }
    } 
    
    
    char first_part[2000] = {0};
    char last_part[2000] = {0};
    // int split_point = -1;

    if (isVowel(word[len-1])){ // Last letter is vowel
        if (isVowel(word[len-2])){ // Last two letters are vowels
            first_part[0] = word[len-1]; // Get the last letter
            first_part[1] = '\0';
            for (int i = 0; i < len-1; i++) { // Copy the rest of the word
                last_part[i] = word[i];
            }
            last_part[len-1] = '\0';
        } else{ // Last letter is vowel, second to last is consonant
            first_part[0] = word[len-2]; // Get second to the last letter
            first_part[1] = word[len-1]; // Get the last letter
            first_part[2] = '\0';
            for (int i = 0; i < len-2; i++) { // Copy the rest of the word
                last_part[i] = word[i];
            }
            last_part[len-2] = '\0';
                
            // }
        }
    } else { // Last letter is a consonant
        if (isVowel(word[len-2])){ // Last letter is consonant, second to last is vowel
            if (isVowel(word[len-3])) { // Third to the last is vowel
                first_part[0] = word[len-2]; // Get the second to last letter
                first_part[1] = word[len-1]; // Get the last letter
                first_part[2] = '\0';
                for (int i = 0; i < len-2; i++) { // Copy the rest of the word
                    last_part[i] = word[i];
                }
                last_part[len-2] = '\0';
            }
            else { // Last letter is consonant, second to last is vowel, third to last is consonant
                first_part[0] = word[len-3]; // Get the third to last letter
                first_part[1] = word[len-2]; // Get the second to last letter
                first_part[2] = word[len-1]; // Get the last letter
                first_part[3] = '\0';
                for (int i = 0; i < len-3; i++) { // Copy the rest of the word
                    last_part[i] = word[i];
                }
                last_part[len-1] = '\0';

            }

        }else if (!isVowel(word[len-2])){ // Last two letters are consonants
            printf("Last two letters are consonants\n");
            first_part[0] = word[len-4]; // Get the fourth last letter
            first_part[1] = word[len-3]; // Get the third last letter
            first_part[2] = word[len-2]; // Get the second letter
            first_part[3] = word[len-1]; // Get the last letter
            first_part[4] = '\0';
            for (int i = 0; i < len-4; i++) { // Copy the rest of the word
                last_part[i] = word[i];
            }
            last_part[len-2] = '\0';
        }

    }

    // Combine the two parts
    strcpy(output, first_part);
    strcat(output, last_part);
    
    
    // Print the transformed word
    printf("Transformed: %s\n", output);
}

int main(void)
{
    int socket_desc, client_sock, client_size;
    // int string_len;
    // int consonant_flag;
    // int i,j, ptr;
    // char c;
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

        transformWord(client_message, server_message);

        // string_len = strlen(client_message);
        // printf("String length: %d\n", string_len);
        // ptr = string_len-1;
        // // Last letter is consonant
        // consonant_flag = !isVowel(client_message[ptr]);
        // for (i = string_len-1; i > 0; i--){
        //     if (consonant_flag){
        //         for ( j = i-2; j <= ptr; j++){
        //             printf("%c", client_message[j]);
        //         }
        //         consonant_flag = 0;
        //         printf("\n");
        //         ptr = i-2;
        //         i=i-2;

        //         for (i = 0; i < ptr; i ++){
        //             printf("%c",client_message[i]);
        //         }
        //         printf("\n");
        //         break;
        //     } else{
        //         for ( j = i-1; j <= ptr; j++){
        //             printf("%c", client_message[j]);
        //         }
        //         printf("\n");
        //         ptr = i-1;
        //         i--;
                
        //         for (i = 0; i < ptr; i ++){
        //             printf("%c",client_message[i]);
        //         }
        //         printf("\n");
        //         break;
        //     }

        // }

        


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
