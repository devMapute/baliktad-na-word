# Filipino Speech Disguise: Tadbalík Translator

This project implements a Filipino speech disguise known as *tadbalík*, a form of *baliktád* where the syllabic structure of words is partially reversed. The program consists of a client-server architecture where the client sends Filipino words or sentences to the server, and the server translates them into *tadbalík* form before sending the response back to the client.

## Features
- Translates Filipino words or sentences into *tadbalík*.
- Retains one-syllable words (e.g., "ng", "ang", "hays") and special cases like "mga" without translation.
- Handles multi-syllable words by reordering syllables (e.g., "maganda" → "damagan").
- Interactive client-server communication over TCP sockets.

## Program Flow
1. **Server Setup**: Start the server program. It listens for incoming client connections.
2. **Client Connection**: The client program prompts the user to input the server's IP address and establishes a connection.
3. **Input and Translation**:
   - The client accepts user input (a Filipino word or sentence).
   - The input is sent to the server.
   - The server translates the input into *tadbalík* and sends the result back to the client.
   - The client prints the translation.
4. **Repeat or Exit**:
   - The client can send another word or exit the program.
   - If the client sends `exit`, the connection is closed.

## Examples
### Input and Output
| Input       | Translation |
|-------------|-------------|
| maganda     | damagan     |
| malupet     | petmalu     |
| meyor       | yorme       |
| pasasalamat | matpasasala |
| ng          | ng          |
| mga         | mga         |
| hirang      | ranghi      |
| natangay    | ngaynata    |



## How to Run
### Prerequisites
- A C compiler (e.g., GCC).
- Both the server and client programs must be compiled and executed on systems that support TCP/IP networking.

### Steps
1. **Compile the Programs**:
   ```bash
   gcc -o server server.c
   gcc -o client client.c
   ```
2. **Run the Server**:
   ```bash
   ./server
   ```
   The server will start listening for incoming connections.

3. **Run the Client**:
   ```bash
   ./client
   ```
   The client will prompt for the server's IP address. Enter the IP address of the machine running the server.

4. **Interact**:
   - Enter Filipino words or sentences in the client program.
   - View the translated *tadbalík* output from the server.

5. **Exit**:
   - Type `exit` in the client program to terminate the connection.

## File Structure
```
.
├── client.c       # Client-side implementation
├── server.c       # Server-side implementation
├── headers.h      # Shared headers for both programs
```

## Notes
- Ensure the server is running before starting the client.
- The server listens on `127.0.0.1` (localhost) by default and port `2000`. Modify the code if a different IP or port is required.
- The client allows dynamic input of the server's IP address.

